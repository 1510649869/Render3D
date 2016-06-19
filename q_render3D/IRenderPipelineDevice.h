#pragma once
#include "Types.h"
class IRenderPipelineDevice
{
public:
	IRenderPipelineDevice();
	~IRenderPipelineDevice();
	bool init(renderInitData data);
	void setWorldMatrix(const Matrix4x4& world);
	void setViewMatrix(const Matrix4x4& view);
	void setProjMatrix(const Matrix4x4& proj);
	void setCameraPos(const  Vector4& pos);
	void setLightingEnable(bool isEnable);
	void setLight(int Index,const DirectionalLight& light);
	void setMaterial(const Material& material);
	void setTexture();
	void Present(int *ptr);
public:
	void drawPoint();      //���Ƶ�
	void drawTriangle(DrawData inData,int* ptr);   //����������
private:
	void  vertexShader(Vertex& inVertex);//���ж���任
	Color vertexLighting(const Point vPosw, const Vector3 vNormalw);//���������
	void  pixelShader(RasterizedFragment& inVertex, int *ptr);

	void  RasterizeTrangles();
	void  RasterizePoint();
	//�����λ���
	int   trangleDevide(Trape* trap,Vertex p1,Vertex p2,Vertex p3);
	void  rasterizeTrangle(Trape *trap);
	void  trapedgeLerp(Trape* trap, float y);
	void  trapinitScanline(Trape* trap,Scanline* scanline,int y);
private:
	float mBufferwidth;
	float mBufferheight;
	std::vector<float>* zBuffer;
	std::vector<unsigned int>* m_pOutColorBuffer;//���������������ɫ
private:
	Matrix4x4 world;
	Matrix4x4 view;
	Matrix4x4 projection;
	Matrix4x4 transform;

	Vector4   cameraPos;
	bool      mLightEnable;
	Material  mMaterial;
	static const UINT	c_maxLightCount = 8;
	DirectionalLight    mLight[c_maxLightCount];
	std::vector<Vertex> screenSpceVertex; //��Ļ�ռ����궥��
	
	std::vector<VertexShaderOut>* m_vertex_homospace; //�ڲü��ռ��еĶ��� ��ʱ-1<x<1 -1<y<1,0<z<1;
	//�ü�����
	void homospaceClipedVertex(std::vector<unsigned int>* const pIndexs);
	void homospaceClipedTriangle(std::vector<unsigned int>* pIndex);
	int  homospaceCheckCvv(const Vector4* pos)
	{
		float w = pos->w;
		int check = 0;
		if (pos->z < 0.0f) check |= 1; //-->check0001
		if (pos->z >  w)   check |= 2;   //-->
		if (pos->x < -w)   check |= 4;   //-->check0111
		if (pos->x >  w)   check |= 8;
		if (pos->y < -w)   check |= 16;
		if (pos->y >  w)   check |= 32;
		return check;
	}

	std::vector<VertexShaderOut>* m_vertex_homospace_cliped;
	std::vector<unsigned int>   * m_index_homospace_cliped;

	std::vector<RasterizedFragment>* m_rasterized;
};

