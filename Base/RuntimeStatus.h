#ifndef __RuntimeStatus_H__
#define __RuntimeStatus_H__

/*
 * Enumeration containing the possible runtime status.
 */
enum RuntimeStatus {

	// The application should continue
	CONTINUE,

	// The application should stop
	FINISH,

	// An error has occurred
	ERROR
};

#endif