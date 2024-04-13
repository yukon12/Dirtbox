#include "perlin.h"

static float ***createVectorGrid(int _m);
static float getValue(float _x, float _y, float ***_vectorGrid, int _m);
static float dotProduct(float _x1, float _y1, float _x2, float _y2);
static float interpolate(float _value1, float _value2, float _weight);

float **createPerlinNoise(int _n, int* _octave, int _octaveNumber)
{
	// Add assertions regarding octaves.
	
	float **_perlinNoise = (float **)malloc(_n*sizeof(float *));
	for(int _x = 0; _x < _n; _x++)
		_perlinNoise[_x] = (float *)malloc(_n*sizeof(float));
	
	for(int _y = 0; _y < _n; _y++)
		for(int _x = 0; _x < _n; _x++)
			_perlinNoise[_x][_y] = 0.0f;
	
	for(int _i = 0; _i < _octaveNumber; _i++)
	{
		int _m = _octave[_i];
		float _cellSize = ((float)_n)/((float)_m);
		float ***_vectorGrid = createVectorGrid(_m);
		
		for(int _y = 0; _y < _n; _y++)
		{
			for(int _x = 0; _x < _n; _x++)
			{
				float _gridX = ((float)_x)/_cellSize;
				float _gridY = ((float)_y)/_cellSize;
				_perlinNoise[_x][_y] += getValue(_gridX, _gridY, _vectorGrid, _m);
			}
		}
	}
	
	return _perlinNoise;
}

static float ***createVectorGrid(int _m)
{
	float ***_vectorGrid = (float ***)malloc(_m*sizeof(float **));
	for(int _x = 0; _x < _m; _x++)
	{
		_vectorGrid[_x] = (float **)malloc(_m*sizeof(float *));
		for(int _y = 0; _y < _m; _y++)
			_vectorGrid[_x][_y] = (float *)malloc(2*sizeof(float));
	}
	
	for(int _y = 0; _y < _m; _y++)
	{
		for(int _x = 0; _x < _m; _x++)
		{
			float _angle = (rand()%360)*0.0175f;
			_vectorGrid[_x][_y][0] = cos(_angle);
			_vectorGrid[_x][_y][1] = sin(_angle);
		}
	}
	
	return _vectorGrid;
}

static float getValue(float _x, float _y, float ***_vectorGrid, int _m)
{
	// Mathematical functions could be added.
	int _x0 = _x;
	int _x1 = (_x0+1)%_m;
	int _y0 = _y;
	int _y1 = (_y0+1)%_m;
	
	float _offsetX = _x-(float)_x0;
	float _offsetY = _y-(float)_y0;
	
	float _topLeft = dotProduct(_offsetX, _offsetY, _vectorGrid[_x0][_y0][0], _vectorGrid[_x0][_y0][1]);
	float _topRight = dotProduct(_offsetX-1.0f, _offsetY, _vectorGrid[_x1][_y0][0], _vectorGrid[_x1][_y0][1]);
	float _bottomLeft = dotProduct(_offsetX, _offsetY-1.0f, _vectorGrid[_x0][_y1][0], _vectorGrid[_x0][_y1][1]);
	float _bottomRight = dotProduct(_offsetX-1.0f, _offsetY-1.0f, _vectorGrid[_x1][_y1][0], _vectorGrid[_x1][_y1][1]);
	
	float _top = interpolate(_topLeft, _topRight, _offsetX);
	float _bottom = interpolate(_bottomLeft, _bottomRight, _offsetX);
	float _value = interpolate(_top, _bottom, _offsetY);
	
	return _value;
}

static float dotProduct(float _x1, float _y1, float _x2, float _y2)
{
	return _x1*_x2+_y1*_y2;
}

static float interpolate(float _value1, float _value2, float _weight)
{
	return (_value2-_value1)*((_weight*(_weight*6.0f-15.0f)+10.0f)*_weight*_weight*_weight)+_value1;	
}