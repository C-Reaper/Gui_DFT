//#include "C:/Wichtig/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"
#include "/home/codeleaded/System/Static/Library/DFT.h"

double actime;
Vec2 cxoffset;
Vec2 cyoffset;
Vec2 offset;
TransformedView tv;
Vector vVales;

Points_Pair points;
FS dftX;
FS dftY;

void Setup(AlxWindow* w){
	tv = TransformedView_Make(
		(Vec2){ GetWidth(),GetHeight() },
		(Vec2){ -600.0f,-400.0f },
		(Vec2){ 0.0015f,0.0015f },
		(float)GetWidth() / (float)GetHeight()
	);

	actime = 0.0f;
	cxoffset = (Vec2){ 0.0f,-250.0f };
	cyoffset = (Vec2){ -250.0f,0.0f };
	offset = (Vec2){ cxoffset.x,cyoffset.y };
	vVales = Vector_New(sizeof(Vec2));
	
	points = DFT_PointsLoad2D("./data/CodingTrain.txt",1);

	dftX = DFT_CalcFS(points.xs.Memory,points.xs.size);
	dftY = DFT_CalcFS(points.ys.Memory,points.ys.size);
}
void Update(AlxWindow* w){
	TransformedView_HandlePanZoom(&tv,window.Strokes,GetMouse());
	Rect r = TransformedView_ScreenWorldRect(&tv,GetScreenRect());

	const double dt = F64_PI2 / (double)dftX.size;
	actime += dt;

	Clear(BLACK);

	FS_Render(WINDOW_STD_ARGS,&tv,cxoffset.x,cxoffset.y,&dftX,0.0,actime);
	FS_Render(WINDOW_STD_ARGS,&tv,cyoffset.x,cyoffset.y,&dftY,F32_PI05,actime);
	
	const Vec2 outx = FS_Calc(&dftX,0.0,actime);
	const Vec2 outy = FS_Calc(&dftY,F32_PI05,actime);
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

	
	if(vVales.size>points.xs.size)
		Vector_PopTop(&vVales);

	for(int i = 1;i<vVales.size;i++){
		Vec2 v0 = *(Vec2*)Vector_Get(&vVales,i-1);
		Vec2 v1 = *(Vec2*)Vector_Get(&vVales,i);

		Vec2 pS = TransformedView_WorldScreenPos(&tv,Vec2_Add(offset,v0));
		Vec2 tS = TransformedView_WorldScreenPos(&tv,Vec2_Add(offset,v1));
		Line_RenderX(WINDOW_STD_ARGS,pS,tS,WHITE,1.0f);
	}

	String str = String_Format("MI: %d",points.xs.size);
	CStr_RenderSizeAlxFont(WINDOW_STD_ARGS,&window.AlxFont,str.Memory,str.size,0.0f,0.0f,WHITE);
	String_Free(&str);
}
void Delete(AlxWindow* w){
	Vector_Free(&vVales);
	Points_Pair_Free(&points);
	FS_Free(&dftX);
	FS_Free(&dftY);
}

int main(){
    if(Create("DFT",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}