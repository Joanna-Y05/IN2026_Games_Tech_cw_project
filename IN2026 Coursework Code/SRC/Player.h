#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameUtil.h"

#include "GameObject.h"
#include "GameObjectType.h"
#include "IPlayerListener.h"
#include "IGameWorldListener.h"
#include "Character.h"

class Player : public IGameWorldListener
{
public:
	Player() {}
	virtual ~Player() {}

	void OnWorldUpdated(GameWorld* world) {}

	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object) {
	
		if (object->GetType() == GameObjectType("Character")) {
			Character* temp = (Character*)object.get();
			mBullets = temp->GetBullets();

		}
		if (object->GetType() == GameObjectType("Ammo")) {
			mBullets -= 1;
			BulletFired();
		}
	}

	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object)
	{
		if (object->GetType() == GameObjectType("Character")) {
			mLives -= 1;
			FirePlayerKilled();
		}
		if (object->GetType() == GameObjectType("CollectibleAmmo")) {
			mBullets += 1;
			BulletCollected();
		}
	}

	void AddListener(shared_ptr<IPlayerListener> listener)
	{
		mListeners.push_back(listener);
	}

	void FirePlayerKilled()
	{
		// Send message to all listeners
		for (PlayerListenerList::iterator lit = mListeners.begin();
			lit != mListeners.end(); ++lit) {
			(*lit)->OnPlayerKilled(mLives);
		}
	}

	void BulletFired()
	{
		// Send message to all listeners
		for (PlayerListenerList::iterator lit = mListeners.begin();
			lit != mListeners.end(); ++lit) {
			(*lit)->OnBulletFired(mBullets);
		}
	}

	void BulletCollected()
	{
		// Send message to all listeners
		for (PlayerListenerList::iterator lit = mListeners.begin();
			lit != mListeners.end(); ++lit) {
			(*lit)->OnBulletCollected(mBullets);
		}
	}


private:
	int mLives;
	int mBullets;

	typedef std::list< shared_ptr<IPlayerListener> > PlayerListenerList;

	PlayerListenerList mListeners;
};

#endif
