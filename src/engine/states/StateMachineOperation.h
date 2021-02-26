#pragma once

class State;

enum class STATE_ID
{
	VOID,
	DEFAULT
};

enum class STATE_MACHINE_OPERATION
{
	CHANGE,
	ADD,
	REMOVE
};

struct StateMachineOperation
{
	StateMachineOperation(const STATE_MACHINE_OPERATION operation, const STATE_ID operand, const std::shared_ptr<State> state = nullptr)
		:
		operation{operation},
		operand{operand},
		state{state}
	{}

	const STATE_MACHINE_OPERATION operation;	// what we're doing to a state (adding, removing, or changing states)
	const STATE_ID operand;		// the state that we're operating on

	const std::shared_ptr<State> state;	// a pointer to the state we're adding (only applicable when operation == ADDING)
};