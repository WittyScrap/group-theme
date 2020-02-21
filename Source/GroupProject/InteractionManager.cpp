// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionManager.h"
#include "InteractionReceiver.h"

void AInteractionManager::Register(AInteractionReceiver* target)
{
	if (Targets.Contains(target->GetID()))
	{
		Targets[target->GetID()].push_back(target);
	}
	else
	{
		std::list<AInteractionReceiver*> nextList;
		nextList.push_back(target);

		Targets.Add(target->GetID(), nextList);
	}
}

void AInteractionManager::Broadcast(const int& requestID, bool stateID)
{
	if (!Targets.Contains(requestID))
	{
		return;
	}

	const std::list<AInteractionReceiver*>& it = Targets[requestID];
	for (AInteractionReceiver* receiver : it)
	{
		receiver->Set(stateID);
	}
}