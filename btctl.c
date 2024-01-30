#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int set_sched_policy(int pid, int policy) {

	/* For cfs task just set to 0 */
	struct sched_param param = {
		.sched_priority = 0,
	};

	if (sched_setscheduler(pid, policy, &param) == -1) {
		printf("%s: failed, args(%d,%d)", __func__, pid, policy);
		exit(EXIT_FAILURE);
	}

	printf("Sched policy set to: %d\n", policy);

	return 0;
}

int get_sched_policy(pid_t pid) {
	int policy = sched_getscheduler(pid);
	if (policy == -1) {
		printf("%s: failed, args(%d)", __func__, pid);
		exit(EXIT_FAILURE);
	}

	printf("Current sched policy is: %d\n", policy);

	return 0;
}

int main(int argc, char *argv[]) {

	if (argc != 3 && argc != 4) {

		printf("\nusage: bt-policy COMMAND [ARGS]\n");
		printf("\nbt-policy commands are:\n");
		printf("  set\t Set sched policy\n");
		printf("  get\t Get sched policy\n");
		printf("\n");

		printf("\nExamples:\n");
		printf("  bt-policy set [pid] [policy]\t Set pid's sched policy\n");
		printf("  bt-policy get [pid]         \t Get pid's sched policy\n");
		printf("\n");

		exit(EXIT_FAILURE);
	}

	pid_t pid;
	int policy;
	char *op = argv[1];

	if (strcmp(op, "get") == 0) {
		pid = atoi(argv[2]);
		get_sched_policy(pid);
	} else if (strcmp(op, "set") == 0) {
		pid = atoi(argv[2]);
		policy = atoi(argv[3]);
		set_sched_policy(pid, policy);
	} else {
		printf("Invalid op");
		exit(EXIT_FAILURE);
	}

	return 0;
}
