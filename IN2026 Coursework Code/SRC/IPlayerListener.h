#ifndef __IPLAYERLISTENER_H__
#define __IPLAYERLISTENER_H__

class IPlayerListener
{
public:
	virtual void OnPlayerKilled(int lives_left) = 0;
	virtual void OnBulletFired(int bullets_left) = 0;
	virtual void OnBulletCollected(int bullets_left) = 0;
	virtual void OnPlayerTakeDamage(int health_left) = 0;
	virtual void OnHeartCollected(int lives_left) = 0;
};

#endif
