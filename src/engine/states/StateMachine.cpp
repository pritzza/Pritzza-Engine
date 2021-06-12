#include "StateMachine.h"

void StateMachine::changeState(const STATE_ID id)
{
	if (states.find(id) != states.end())	// only change to a state that exists
		currentStateID = id;
}

void StateMachine::addState(const STATE_ID id, const std::shared_ptr<State>& state)
{
	if(states.find(id) == states.end())		// only add a state if it doesnt exist yet
		states.insert({ id, state });
}

void StateMachine::removeState(const STATE_ID id)
{
	if (states.find(id) != states.end())	// only remove state that does exist
	{
		states.at(id)->unload();
		states.erase(id);
	}
}

void StateMachine::processChanges()
{
	for (auto& op : operationQueue)
		switch (op.operation)
		{
		case STATE_MACHINE_OPERATION::ADD:		addState   (op.operand, op.state);	break;
		case STATE_MACHINE_OPERATION::REMOVE:	removeState(op.operand);			break;
		case STATE_MACHINE_OPERATION::CHANGE:	changeState(op.operand);			break;
		}

	operationQueue.clear();
}

void StateMachine::queueOperation(const StateMachineEvent& operation)
{
	operationQueue.push_back(operation);
}

const bool StateMachine::isStateLoaded(const STATE_ID state) const
{
	return this->states.find(state) != states.end();
}

const int StateMachine::getSize() const
{
	return this->states.size();
}

const std::shared_ptr<State> StateMachine::currentState() const
{
	if (states.at(currentStateID) != nullptr)
		return states.at(currentStateID);

	return nullptr;
}
