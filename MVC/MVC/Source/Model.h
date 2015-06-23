#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>

class Model
{
public:
	Model(void);
	~Model(void);

	// Update the model
	virtual void Update(void);
};

#endif