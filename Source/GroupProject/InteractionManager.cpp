// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionManager.h"
#include "InteractionReceiver.h"

void AInteractionManager::Register(AInteractionReceiver* target)
{
	if (Targets.Contains(target->GetID()))
	{
		TLinkedList<AInteractionReceiver*> list_target = TLinkedList<AInteractionReceiver*>(target);
		TLinkedList<AInteractionReceiver*>* node = &list_target;
		Targets[target->GetID()].LinkHead(node);
	}
	else
	{
		Targets[target->GetID()] = TLinkedList<AInteractionReceiver*>(target);
	}
}

void AInteractionManager::Broadcast(const int& requestID, bool stateID)
{
	if (!Targets.Contains(requestID))
	{
		return;
	}

	TLinkedList<AInteractionReceiver*> it = Targets[requestID];

	for (; it.GetNextLink() != nullptr; it = *it.GetNextLink())
	{
		AInteractionReceiver* receiver = *it;

		if (stateID)
		{
			receiver->OnSet();
		}
		else
		{
			receiver->OnUnset();
		}
	}
}
