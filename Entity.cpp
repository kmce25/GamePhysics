class Entity
{
public:
	virtual void update(float dt) = 0;
	virtual void draw(int width, int height) = 0;
};