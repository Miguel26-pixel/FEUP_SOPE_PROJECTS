#include "tasks.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t empty;
sem_t full;

int public_fifo;

int process_tasks(int argc, char* argv[]) {
    
    initQueue((argc == 4) ? 10 : atoi(argv[4]));

    char name[2000];
    snprintf(name, sizeof(name), "%s", argv[argc - 1]);

    if ((public_fifo = open(name, O_RDONLY | O_NONBLOCK)) < 0 ) {
        perror("ERROR - open");
        return 1;
    }

    if (sem_init(&empty, 0, size()) != 0 || sem_init(&full, 0, 0)) {
        perror("ERROR - sem_init");
        return 1;
    }

    pthread_t sc;  

    pthread_create(&sc, NULL, process_sc, NULL);

    int n_threads = 0, n_messages = 0;
    pthread_t * ids = malloc(sizeof(pthread_t));
    struct message m;
    int r;
    while ((r = recieve_message(argc, argv, &m)) == 0 || check_time(argc, argv)) {

        if (r != 0) { continue; }

        struct message * sms = malloc(sizeof(struct message));
        *sms = m;

        struct argCV * args = malloc(sizeof(struct argCV));
        args->argc = argc;
        args->argv = argv;
        args->msg = sms;

        ids = realloc(ids, (n_threads + 1)*sizeof(pthread_t));

        if(pthread_create(&ids[n_threads],NULL,process_threads,(void*)args) != 0) {
			perror("ERROR - pthread_create");
			exit(3);
		}
        n_threads++;
        n_messages++;
    }

    close(public_fifo);

    while (getNumMessages() != n_messages) ;

    notify_finish();
    
    pthread_join(sc, NULL);
    
    for (int i = 0; i < n_threads; i++) {
        pthread_join(ids[i], NULL);
    }
    
    sem_destroy(&empty);
    sem_destroy(&full);

    unlink_publicFIFO(argc,argv);
    
    freeQueue();

    free(ids);

    return 0;
}

void* process_threads(void *arg) {

    struct argCV args = *(struct argCV*)arg;

    free(arg);

    if (check_time(args.argc, args.argv))
        args.msg->tskres = task(args.msg->tskload);

    if (check_time(args.argc, args.argv)) {
        register_message(args.msg, "TSKEX");
    } else {
        args.msg->tskres = -1;
    }

    insert_message(args.msg);

    return NULL;
}

void * process_sc(void* arg) { 
    struct message* sms;

    while (1) {
        if (sem_wait(&full) != 0) { continue; }

        pthread_mutex_lock(&mutex);
        sms = pop();
        pthread_mutex_unlock(&mutex);

        if (sem_post(&empty) != 0) { perror("ERROR - sem_post"); }

        if (sms->tskres == -9999) { free(sms); break; }

        char path[2000];
        snprintf(path, sizeof(path), "/tmp/%d.%ld", sms->pid, sms->tid);

        send_message(sms, path);

        free_message(sms, path);
    }

    while(!isEmpty()) {
        pthread_mutex_lock(&mutex);
        sms = pop();
        pthread_mutex_unlock(&mutex);

        char path[2000];
        snprintf(path, sizeof(path), "/tmp/%d.%ld", sms->pid, sms->tid);

        send_message(sms, path);
        free_message(sms, path);
    }
    
    return NULL;
 }


void free_message(struct message * sms, char * path) {
    while (access(path, F_OK) == 0) ;
    free(sms);
}
