//#include "C:/Wichtig/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"
#include "/home/codeleaded/System/Static/Library/DFT.h"

double actime;
double speed;
Vec2 cxoffset;
Vec2 cyoffset;
Vec2 offset;
TransformedView tv;
Vector vVales;

#define DFT_SIZE	1000
double* pointsX;
double* pointsY;
Vec2* dftX;
Vec2* dftY;

void Setup(AlxWindow* w){
	tv = TransformedView_Make(
		(Vec2){ GetWidth(),GetHeight() },
		(Vec2){ 0.0f,0.0f },
		(Vec2){ 0.1f,0.1f },
		(float)GetWidth() / (float)GetHeight()
	);

	actime = 0.0f;
	speed = 0.001f;
	cxoffset = (Vec2){ 2.0f,0.0f };
	cyoffset = (Vec2){ 0.0f,2.0f };
	offset = (Vec2){ cxoffset.x,cyoffset.y };
	vVales = Vector_New(sizeof(double));

	//pointsX = DFT_PointsFunc(0.0,F64_PI2,DFT_SIZE,cos);
	//pointsY = DFT_PointsFunc(0.0,F64_PI2,DFT_SIZE,sin);

	pointsX = DFT_PointsFunc(0.0,F64_PI2,DFT_SIZE,cos);
	pointsY = DFT_PointsFunc(0.0,F64_PI2,DFT_SIZE,sin);
	
	dftX = DFT_CalcP(pointsX,DFT_SIZE);
	dftY = DFT_CalcP(pointsY,DFT_SIZE);
}
void Update(AlxWindow* w){
	TransformedView_HandlePanZoom(&tv,window.Strokes,GetMouse());
	Rect r = TransformedView_ScreenWorldRect(&tv,GetScreenRect());

	const double dt = F32_PI2 / (double)DFT_SIZE;
	actime += dt;

	Clear(BLACK);

	DFT_Render(WINDOW_STD_ARGS,&tv,cxoffset.x,cxoffset.y,dftX,DFT_SIZE,speed,actime);
	DFT_Render(WINDOW_STD_ARGS,&tv,cyoffset.x,cyoffset.y,dftY,DFT_SIZE,speed,actime);
	
	const Vec2 outx = DFT_Calc(dftX,DFT_SIZE,speed,actime);
	const Vec2 outy = DFT_Calc(dftY,DFT_SIZE,speed,actime);
	const Vec2 v = {
		outx.x,
		outy.y
	};
	Vector_Add(
		&vVales,
		(Vec2[]){v},0
	);

	Vec2 xpS = TransformedView_WorldScreenPos(&tv,Vec2_Add(cxoffset,outx));
	Vec2 xtS = TransformedView_WorldScreenPos(&tv,Vec2_Add(offset,v));
	Line_RenderX(WINDOW_STD_ARGS,xpS,xtS,WHITE,1.0f);

	Vec2 ypS = TransformedView_WorldScreenPos(&tv,Vec2_Add(cyoffset,outy));
	Vec2 ytS = TransformedView_WorldScreenPos(&tv,Vec2_Add(offset,v));
	Line_RenderX(WINDOW_STD_ARGS,ypS,ytS,WHITE,1.0f);

	
	if(vVales.size>DFT_SIZE)
		Vector_PopTop(&vVales);

	for(int i = 1;i<vVales.size;i++){
		Vec2 v0 = *(Vec2*)Vector_Get(&vVales,i-1);
		Vec2 v1 = *(Vec2*)Vector_Get(&vVales,i);

		Vec2 pS = TransformedView_WorldScreenPos(&tv,Vec2_Add(offset,v0));
		Vec2 tS = TransformedView_WorldScreenPos(&tv,Vec2_Add(offset,v1));
		Line_RenderX(WINDOW_STD_ARGS,pS,tS,WHITE,1.0f);
	}

	String str = String_Format("MI:%d",DFT_SIZE);
	CStr_RenderSizeAlxFont(WINDOW_STD_ARGS,&window.AlxFont,str.Memory,str.size,0.0f,0.0f,WHITE);
	String_Free(&str);
}
void Delete(AlxWindow* w){
	Vector_Free(&vVales);
	
	if(pointsX) free(pointsX);
	pointsX = NULL;
	if(pointsY) free(pointsY);
	pointsY = NULL;

	if(dftX) free(dftX);
	dftX = NULL;
	if(dftY) free(dftY);
	dftY = NULL;
}

int main(){
    if(Create("DFT",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}