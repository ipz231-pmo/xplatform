#include "main.h"
#include <stddef.h>

typedef void (*callbackType)();

#define MAX_CALLBACKS_COUNT 50

struct EventHandler
{
	size_t callbacksCount;
	callbackType callbacks[MAX_CALLBACKS_COUNT];

};

void initEvent(struct EventHandler* e)
{
	e->callbacksCount = 0;
	for (int i = 0; i < MAX_CALLBACKS_COUNT; i++)
	{
		e->callbacks[i] = NULL;
	}
}

void addCallback(struct EventHandler* e, callbackType callback)
{
	if (e->callbacksCount >= MAX_CALLBACKS_COUNT)
		exit(); // size limit`


}

int main() 
{
	int g = HEAD;
}