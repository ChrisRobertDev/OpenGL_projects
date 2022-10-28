#pragma once
class JumpingListener : public b2ContactListener
{
public:
	int numFootContacts = 0;
	
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

