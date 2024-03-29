#pragma once

#include <unordered_map>
#include <memory>

#include "State.h"
#include "StateMachineEvent.h"

class StateMachine
{
private:
	std::unordered_map<STATE_ID, std::shared_ptr<State>> states;

	STATE_ID currentStateID;

	std::vector<StateMachineEvent> operationQueue;
 
private:
	void changeState(const STATE_ID id);	// changes the current state without modifying any other existing states
	void addState(const STATE_ID id, const std::shared_ptr<State>& state);	// inserts a new state at a STATE_ID key
	void removeState(const STATE_ID id);	// removes a state at a STATE_ID key

public:
	void processChanges();	// iterates through operationQueue to see what operations need to be done

	void queueOperation(const StateMachineEvent& operation);

	const bool isStateLoaded(const STATE_ID state) const;

	const int getSize() const;
	const std::shared_ptr<State> currentState() const;
};