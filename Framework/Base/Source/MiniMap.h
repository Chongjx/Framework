#ifndef MINI_MAP_H
#define MINI_MAP_H

#include "Mesh.h" 
#include <vector>

struct Avatar
{
	Avatar();
	~Avatar();
	Mesh* avatarMesh;
	float xCoord;
	float yCoord;
	float angle;
	bool render;

	// Set the Avatar mesh to this class 
	bool setAvatar(Mesh* anAvatar);
	bool setAngle(const float angle);
	bool setPosition(const float x, const float y);
	bool setRender(bool render);
	
	// Get the Avatar mesh to this class 
	Mesh* getAvatar(void) const;
	float getAngle(void) const;	
	float getPosition_x(void); 	
	float getPosition_y(void);
	bool getRender(void) const;
};

class MiniMap 
{
public: 
	MiniMap(void);  	
	virtual ~MiniMap(void); 

	Mesh* m_MiniMap_Background;  	
	Mesh* m_MiniMap_Border;
	Avatar player;
	std::vector<Avatar> enemyList;
	std::vector<Avatar> statictList;

	// Set the background mesh to this class  	
	bool setBackground(Mesh* aBackground);  	
	// Get the background mesh to this class  	
	Mesh* getBackground(void); 
	// Set the Border mesh to this class  	
	bool setBorder(Mesh* aBorder);  	
	// Get the Border mesh to this class 
	Mesh* getBorder(void);  

	// Set size of minimap (for calculation of avatar in minimap)
	bool setSize(const float x, const float y);

	// Get size of minimap (for calculation of avatar in minimap)  
	float getSize_x(void); 
	// Get size of minimap (for calculation of avatar in minimap)  	
	float getSize_y(void); 
private: 
	// Minimap size  	
	float size_x, size_y; 
};  

#endif