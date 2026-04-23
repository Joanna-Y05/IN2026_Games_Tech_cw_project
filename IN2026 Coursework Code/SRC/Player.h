#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameUtil.h"

#include "GameObject.h"
#include "GameObjectType.h"
#include "IPlayerListener.h"
#include "IGameWorldListener.h"
#include "Character.h"
#include "Enemy.h"

class Player : public IGameWorldListener
{
public:
	Player() {}
	virtual ~Player() {}

	void OnWorldUpdated(GameWorld* world) {}

	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object) {
		if (object->GetType() == GameObjectType("Ammo")) {
			mBullets -= 1;
			BulletFired();
		}
	}

	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object)
	{
		if (object->GetType() == GameObjectType("Character")) {
			mLives -= 1;
			mHealth = 20;
			FirePlayerKilled();
			DamageTaken();
		}
		if (object->GetType() == GameObjectType("CollectibleAmmo")) {
			mBullets += 1;
			BulletCollected();
		}
		if (object->GetType() == GameObjectType("CollectibleLife")) {
			mLives += 1;
			HeartCollected();
		}

		//Right now this also means when u shoot an enemy
		if (object->GetType() == GameObjectType("Enemy")) {
			Enemy* temp = (Enemy*)object.get();
			
			if (temp->GetWhoKilled() == false) {
				mHealth -= temp->GetPower();
				DamageTaken();
			}
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

	void HeartCollected()
	{
		// Send message to all listeners
		for (PlayerListenerList::iterator lit = mListeners.begin();
			lit != mListeners.end(); ++lit) {
			(*lit)->OnHeartCollected(mLives);
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

	void DamageTaken()
	{
		// Send message to all listeners
		for (PlayerListenerList::iterator lit = mListeners.begin();
			lit != mListeners.end(); ++lit) {
			if (mHealth < 0) { mHealth = 0; }
			(*lit)->OnPlayerTakeDamage(mHealth);
		}
	}


private:
	int mLives = 3;
	int mBullets = 6;
	int mHealth = 20;

	typedef std::list< shared_ptr<IPlayerListener> > PlayerListenerList;

	PlayerListenerList mListeners;
};

#endif
