typedef struct Infos_t {
	int n;
	int l, r;
} infos_t;

int* full_v;

void* mergeMT(infos_t* infos) {
	sort(full_v, infos);
}

void* mergeSortMT(void* infos_MT) {
	infos_t* infos = (infos_t*) infos_MT;	
	thread_t left_t, right_t;
	int l, m, r;

	if (infos->n == 1)
		pthread_exit(0);

	l = infos->l;
	r = infos->r;
	m = (r - l)/2;	

	left = (infos_t*) malloc(sizeof(infos_t));
	left->l = l;
	left->r = m;

	right = (infos_t*) malloc(sizeof(infos_t));
	right->l = m+1;
	right->r = r;	

	pthread_create(&left_t, NULL, mergeSortMT, left);
	pthread_create(&right_t, NULL, mergeSortMT, right);

	pthread_join(&left_t);
	pthread_join(&right_t);

	mergeMT(infos);
	
	pthread_exit(0);
}