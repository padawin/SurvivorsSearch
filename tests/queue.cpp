#include "src/Queue.hpp"
#include <stdio.h>

int main() {
	Queue q;

	q.push("foo");
	q.push("bar");
	q.push("toto");
	q.push("tata");

	S_QueueItem *cur;
	while ((cur = q.next())) {
		printf("Queue item: %s\n", cur->value);
	}

	q.pop();
	q.reset();

	while ((cur = q.next())) {
		printf("Queue item: %s\n", cur->value);
	}

	q.clear();
	return 0;
}
