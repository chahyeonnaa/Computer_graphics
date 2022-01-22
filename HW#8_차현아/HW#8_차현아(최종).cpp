/***********************************************************************/
/*                 HW#8 : 종합                                         */
/*  작성자 : 차현아                           날짜 : 2021년 12월 3일   */
/*                                                                     */
/* 문제 정의 : 지금까지 수행한 과제 내용을 종합하여 객체 모델링        */
/*            요구사항 -  총 8개의 기술사용                            */
/* 제목 : 메리크리스마스                                               */
/*     크리스마스 트리에 눈이 내리는 모습을 묘사하였습니다.            */
/*     트리에는 별과 오너먼트들을 달고,아래에는 선물을 배치하였습니다. */
/*     선물은 텍스쳐매핑을 이용하여 포장지로 포장 하였습니다           */
/*     두개의 조명을 트리의 앞뒤로 다른위치에 배치하여 은은하게 조명을 비추었습니다. */
/*     메뉴콜백을 이용하여 선물을 확인할 수 있습니다.                       */
/*     선물은 정육면체에 저희집 고양이 사진을 텍스쳐매핑한 사진육면체입니다.*/
/*     키보드 콜백을 통해 눈내림과 조명밝기를 조정할 수 있습니다.           */
/*     선물 포장지는 코드 10-5를 참고하였습니다.         */
/***********************************************************************/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>  // 유틸리티 함수인 auxDIBImageLoad()함수 사용
#include <GL/glu.h>
#include <stdio.h>

#pragma comment(lib, "glaux.lib")
#pragma comment (lib,"legacy_stdio_definitions.lib")

unsigned int MyTextureObject[2]; // 텍스쳐 객체 이름할당 공간(텍스쳐 객체 2개 -> 선물띠, 고양이사진)
AUX_RGBImageRec* pTextureImage[1]; //텍스쳐 저장 공간을 가리키는 포인터(이미지 로드)

int Width, Height;

GLfloat snow = 0.0;
int Stop = 0; // 뷰폿변환과 관련된 변수
static bool Case; // 눈내림제어

const GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
const GLfloat orange[] = { 1.0, 0.5, 0.0, 1.0 };
const GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
const GLfloat green[] = { 0.2, 1.0, 0.0, 1.0 };
const GLfloat blue[] = { 0.0, 1.0, 1.0, 1.0 };
const GLfloat purple[] = { 0.25, 0.0, 0.5, 1.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat brown[] = { 0.7, 0.25, 0.25, 1.0 };
const GLfloat light_pos[] = { 2.0, 3.0, 4.0, 1.0 };
const GLfloat light_pos2[] = { 10.0, 10.0, -8.0, 1.0 };
// 조명 2개 사용
GLfloat Const = 5.0; // 조명- 감쇠비율상수값
GLfloat Const2 = 6.0; // 조명- 감쇠비율상수값
GLfloat ref_plane[] = { 1.5, 1.5, 1.5, 0.0 };   // 1D 텍스쳐 기준평면

#define stripeImageWidth    32
GLubyte stripeImage[4 * stripeImageWidth];   // 1D 텍스쳐 배열(선물포장지)

// BMP 파일을 불러오는 함수
AUX_RGBImageRec* LoadBMP(char* szFilename) { // 텍스쳐 파일을 배열로 바꿔주는 함수(텍스쳐는 배열형태로 저장되어야함)

	FILE* pFile = NULL;
	if (!szFilename) {
		return NULL;
	}
	fopen_s(&pFile, szFilename, "r");

	// seFilename을 유니코드 스트링으로 바꾸기
	int size = strlen(szFilename);
	wchar_t* w_szFilename = new wchar_t[size];

	for (int i = 0; i < size; ++i)  w_szFilename[i] = szFilename[i];
	w_szFilename[size] = NULL;

	if (pFile) {
		fclose(pFile);
		return auxDIBImageLoad(w_szFilename);     //파일로부터 메모리로	
	}
	return NULL;
}

// 텍스쳐 영상 파일을 메모리배열로 로드하고, 텍스쳐 메모리로 올리기
int LoadGLTextures(char* szFilePath) { //파일을 로드하고 텍스쳐로 변환

	int Status = FALSE;
	glClearColor(0.0, 0.0, 0.0, 0.5);
	memset(pTextureImage, 0, sizeof(void*) * 1); //이미지가 들어갈 배열(포인터)를 널로 초기화

	if (pTextureImage[0] = LoadBMP(szFilePath)) {   //비트맵을 로드하고 오류확인
		Status = TRUE; // 이미지를 잘 불러왔으면 true로 세팅                             
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[1]); // 객체 생성
		// 텍스쳐메모리에 올리기
		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
		// 텍스쳐파라미터 명시
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 선형보간
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D); // 2D 텍스쳐 매핑 활성화
	}
	if (pTextureImage[0]) { // 텍스쳐 영상 메모리 배열이 존재하면                
		if (pTextureImage[0]->data) { // 텍스쳐 영상 메모리 배열 안에 실제 영상이 존재하면
			free(pTextureImage[0]->data); //텍스쳐 영상공간 반납
		}
		free(pTextureImage[0]); //텍스쳐 반납
	}
	return Status;
}
void MyDisplay2(void) // 육면체 그리기(수동매핑)
{
	const char* szFilename = "Namu.bmp"; // 사진 불러오기
	LoadGLTextures((char*)szFilename); //LoadGLTextures 안에서 텍스쳐 이미지를 배열로 불러오기

	// 조명효과 및 glColor 무시하고, 텍스쳐 사진만 입히기(GL_REPLACE)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_TEXTURE_GEN_S); // 1D 자동매핑 활성화 끄기- 안꺼주면 선물띠 문양이 입혀짐
	glBindTexture(GL_TEXTURE_2D, MyTextureObject[1]); // 텍스쳐 객체 생성
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, -1.0f, 3.0f);  //앞면
	glTexCoord2f(1.0f, 0.0f); glVertex3f(12.0f, -1.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(12.0f, 3.0f, 3.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(7.0f, 3.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(7.0f, -1.0f, -1.0f);  //뒷면
	glTexCoord2f(1.0f, 1.0f); glVertex3f(7.0f, 3.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(12.0f, 3.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(12.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(7.0f, 3.0f, -1.0f);  //윗면
	glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, 3.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(12.0f, 3.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(12.0f, 3.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(7.0f, -1.0f, -1.0f);  //아랫면
	glTexCoord2f(0.0f, 1.0f); glVertex3f(12.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(12.0f, -1.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(7.0f, -1.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(12.0f, -1.0f, -1.0f);  //우측면
	glTexCoord2f(1.0f, 1.0f); glVertex3f(12.0f, 3.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(12.0f, 3.0f, 3.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(12.0f, -1.0f, 3.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, -1.0f, -1.0f);  //좌측면
	glTexCoord2f(1.0f, 0.0f); glVertex3f(7.0f, -1.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(7.0f, 3.0f, 3.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(7.0f, 3.0f, -1.0f);
	glEnd();

}
void MyStripeImage() { // 선물에 매핑될 텍스쳐 생성함수 (정사각형에 선물띠를 두름)                            
	for (int j = 0; j < stripeImageWidth; j++) {
		stripeImage[4 * j] = 255;
		stripeImage[4 * j + 1] = (j < 8) ? 0 : 255;
		stripeImage[4 * j + 2] = (j < 8) ? 0 : 255;
		stripeImage[4 * j + 3] = 0;
	}
}
void MyInit2(void) {

	MyStripeImage(); // 선물 띠 만들기
	glBindTexture(GL_TEXTURE_1D, MyTextureObject[0]); // 텍스쳐 객체 생성(MyTextureObject의 0번 배열)
	// 텍스쳐메모리에 올리기(그림이므로 1D, 텍스쳐데이터가 저장된 곳에 대한 포인터 (= 배열이름))
	glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
	// 텍스쳐좌표 자동매핑(물체좌표기준)
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	// 기준평면 설정
	glTexGenfv(GL_S, GL_OBJECT_PLANE, ref_plane);
	// 텍스쳐 파라미터 명시
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 선형보간사용
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 선형보간 사용
	// 텍스쳐 환경 명시 (물체면 색깔과 텍스쳐색을 곱해서 최종 색 결정- 조명효과 보존하면서 입히기)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_TEXTURE_GEN_S); // 텍스쳐 자동매핑 활성화
	glEnable(GL_TEXTURE_1D); // 1D 텍스쳐 매핑 활성화
}

void MyTimer2(int Value) { // 지속적인 눈내림을 위한 타이머
	if (Case == false) // Case의 초기값을 false로 설정하여, 항상 눈이내리도록 하였음
	{
		snow = snow + 0.05; // 눈들의 위치가 아래로 0.05씩 떨어짐
		if (snow >= 3.5) // 적당히 아래로 내려왔으면
			snow = 0; // 원래위치로 돌아가도록 하였음
		glutPostRedisplay();
		glutTimerFunc(55, MyTimer2, 1); // 인위적으로 타이머이벤트 발생시켜주기
	}
	else
		glutPostRedisplay();

}
void MyKeyboard(unsigned char key, int x, int y) { // 키보드 조작을 통해 눈내림 조작가능
	switch (key) {
	case 'Z': // z or Z를 누르면, Case값을 변경하여 눈이 내리거나 눈이 멈추게 할 수 있음
	case 'z': // 초기값은 false로 눈이 항상 내리고있음
		if (Case == false) { // 눈이 내리고 있는상황에서
			Case = true; // 눈 멈춤
		}
		else if (Case == true) { // 눈이 멈춘 상황에서
			Case = false; // 다시 눈 내리게 하기
			glutTimerFunc(55, MyTimer2, 1); // 눈내림 타이머 호출
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();
}
void MySpecial(int key, int x, int y) { // 방향키 조작 = 조명세기 조작가능
	switch (key) {
	case GLUT_KEY_UP: // 윗방향키를 누르면, 두개의 조명모두 밝기증가
		Const -= 0.5;
		Const2 -= 0.5;
		if (Const <= 2.0 || Const2 <= 2.0) { // 특정밝기이상 밝아지도록 하지 못하게하였음(조명 한계치설정)
			Const = 2.0;
			Const2 = 2.0;
		}
		break;
	case GLUT_KEY_DOWN: // 아래방향키, 두개의 조명 모두 밝기 감소
		Const += 0.5;
		Const2 += 0.5;
		break;
	default:
		break;
	}
	glutPostRedisplay(); // 디스플레이 이벤트 강제 발생시키기
}

void MyMainMenu(int entryID) { // 주메뉴
	if (entryID == 1) // 각 항목 클릭시 Stop값 조정
		Stop = 1;
	else if (entryID == 2)
	{
		Stop = 3;
	}
	glutPostRedisplay(); // 디스플레이콜백 강제발생시키기
}
void MyInit(void) { // 실행에 필요한 초기값들 설정

	glGenTextures(2, MyTextureObject); // 텍스쳐객체를 2개 생성하기 위해서 준비

	glutAddMenuEntry("Open the gift !", 1); // 메뉴항목첨가
	glutAddMenuEntry("Come back !", 2); //(항목의 이름, 항목이 선택될때 메뉴콜백함수에게 전달되는 정수값)
	glutAttachMenu(GLUT_RIGHT_BUTTON); // 오른쪽 버튼 클릭시 메뉴가 뜸

	glMatrixMode(GL_PROJECTION); // 투영행렬스택
	glLoadIdentity();

	glClearColor(0.0, 0.0, 0.0, 1.0); // 배경색은 검은색
	glEnable(GL_DEPTH_TEST); // 명시적으로 은면제거 계산을 하도록 설정
	glEnable(GL_CULL_FACE); // 후면제거모드 활성화
	glCullFace(GL_BACK);

}

void MyDisplay(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색버퍼 초기화하면서 깊이버퍼도 초기화(은면제거를 위함)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 시점변환
	if (Stop == 1) // 1번 메뉴 클릭시, 시점이 이동되면서 준비된 선물이 보여짐
	{
		// 트리의 옆쪽으로 시점 이동(선물을 보여주기 위해)
		gluLookAt(0.5 + 12.0, 0.5, 4.0, 0.0 + 12.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		// 뷰폿을 4개로 분할하였음
		glViewport(0, 0, Width / 2, Height / 2);
		MyDisplay2(); // 우리집 고양이 사진을 입힌 정육면체 등장

		glViewport(Width / 2, 0, Width / 2, Height / 2);
		MyDisplay2(); // 우리집 고양이 사진을 입힌 정육면체 등장

		glViewport(0, Height / 2, Width / 2, Height / 2);
		MyDisplay2();
		glViewport(Width / 2, Height / 2, Width / 2, Height / 2);
		MyDisplay2();

	}
	else if (Stop == 3) // 2번 메뉴 클릭시, 트리가 있는 위치로 돌아옴
	{
		gluLookAt(0.5, 0.5, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		// 트리로 돌아올때, 2D 활성화를 꺼주지않으면 트리에 2D이미지가 입혀짐
		glDisable(GL_TEXTURE_2D); // 반드시 필요
		glViewport(0, 0, Width, Height);

	}
	else if (Stop == 0) // 초기상태시점
	{
		gluLookAt(0.5, 0.5, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	// 조명은 두개를 사용하였음
	glEnable(GL_LIGHT0); // 0번 조명 활성화
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Const); // 감쇠비율 상수값 설정(방향키 조작 -> Const값 조작)
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); // 0번 광원의 위치
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white); // 0번광원의 난반사광의 색을 흰색으로 설정(전체적인 명암부여)
	glLightfv(GL_LIGHT0, GL_SPECULAR, white); // 0번 광원의 정반사광의 색을 흰색으로 설정

	glEnable(GL_LIGHT1); // 1번 조명 활성화
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white); // 1번광원의 난반사광의 색을 흰색으로 설정(전체적인 명암부여)
	glLightfv(GL_LIGHT1, GL_SPECULAR, white); // 1번 광원의 정반사광의 색을 흰색으로 설정
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Const2);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);



	glPushMatrix();

	// 눈그리기 (총 16개 그림- 적당히 여러군데에 퍼져있도록)
	glPushMatrix();
	glTranslatef(2.0, 7.0 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 6.5 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.5, 5.8 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 4.5 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈4
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 5.2 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈5
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 3.7 - snow + 0.6, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈6
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 4.5 - snow + 0.8, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈7
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 3.4 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈8
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5, 5.0 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈9
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, 3.2 - snow + 1.0, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈10
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.0, 4.2 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈11
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, 5.5 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈12
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 5.0 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈13
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.3, 5.9 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈14
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.9, 6.9 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈15
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 6.0 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // 눈16
	glPopMatrix();
	// 눈그리기 끝

	// 트리에 선긋기(장식을 매달아놓는 줄)
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0); // 선색은 흰색
	glLineWidth(1.0); // 선굵기 설정
	glBegin(GL_LINES);
	glVertex3f(-0.4, 4.5, 1.5);
	glVertex3f(1.5, 3.8, 0.8);
	glEnd();
	glFlush();

	glBegin(GL_LINES);
	glVertex3f(1.5, 3.8, 0.8);
	glVertex3f(-2.1, 2.3, 3.0);
	glEnd();
	glFlush();

	glBegin(GL_LINES);
	glVertex3f(-2.1, 2.3, 3.0);
	glVertex3f(3.9, 1.7, 4.1);
	glEnd();
	glFlush();

	// 별그리기
	// 위치값을 잘 잡아서 삼각형 두개를 덧대어 그려 별처럼 보이게 하였음
	glColor3f(1.0, 1.0, 0.0); // 노란색
	glBegin(GL_POLYGON); // 삼각형 1
	glVertex3f(0.6, 5.4, 0.0);
	glVertex3f(0.0, 6.26, 0.0);
	glVertex3f(-0.6, 5.4, 0.0);
	glEnd();
	glFlush();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON); // 삼각형 2
	glVertex3f(0.6, 5.9, 0.0);
	glVertex3f(-0.6, 5.9, 0.0);
	glVertex3f(0.0, 5.2, 0.0);
	glEnd();
	glFlush();

	// 눈과 장식줄, 별에는 조명효과가 적용이 안되게 하기 위해서 모두 다 그린후, 조명 활성화
	glEnable(GL_LIGHTING);

	// 장식그리기(총 9개의 장식)
	// 트리 선에 줄줄이 매달려있도록 구현
	// 모든 장식의 주변반사 및 난반사에 대한 물체색을 다르게 설정하였음
	// SolidSphere 로 동그란 모양의 장식을 만들었음
	glPushMatrix();
	glTranslatef(0.0, 4.6, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown); // 물체면 특성 정의(주변반사와 난반사에 대한 물체색)
	glMaterialfv(GL_FRONT, GL_SPECULAR, white); // 정반사광계수 설정
	glutSolidSphere(0.3, 30, 30); // 장식 1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, 4.4, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // 장식 2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, 3.5, 2.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // 장식 3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 3.1, 2.4);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // 장식 4
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.9, 2.7, 2.5);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // 장식 5
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 1.9, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // 장식 6
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 1.65, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // 장식 7
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1.53, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // 장식 8
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 1.35, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // 장식 9
	glPopMatrix();

	// 장식그리기 끝
	// 트리그리기- SolidCone으로 트리형태 구현
	glPushMatrix();
	glTranslatef(0.0, 0.9, 0.0);
	glScalef(3.0, 3.0, 3.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green); // 트리색은 초록색
	glMaterialfv(GL_FRONT, GL_SPECULAR, green);
	glutSolidCone(1.1, 1.5, 30, 30); // 트리
	glPopMatrix();

	// 트리 받침나무 그리기
	glPushMatrix();
	glTranslatef(0.0, -0.5, 0.0);
	glScalef(1.0, 2.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brown);
	glutSolidCube(1.5); //나무
	glPopMatrix();

	// 선물그리기- SolidCube로 정사각형 모양으로 만들었음
	// MyInit2()을 통해 4개의 선물 전체에 띠무늬 입히기
	// 다른 선물에 의해 가려진 부분은 보이지않음(은면제거)
	glPushMatrix();
	glTranslatef(2.3, -1.2, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	MyInit2();
	glutSolidCube(1.0); //선물1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.3, -1.2, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
	glutSolidCube(1.0);//선물2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.3, -1.4, 2.5);
	glScalef(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidCube(1.0);// 선물3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.4, -1.4, 2.5);
	glScalef(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidCube(1.0);// 선물4
	glPopMatrix();

	glDisable(GL_TEXTURE_1D); // 그림 전체에 띠무늬가 입혀져 텍스춰매핑이 일어나므로 그것을 방지하기 위해 비활성화
	glDisable(GL_LIGHTING); // 필요한 부분에만 조명을 입히기위해 마찬가지로 비활성화시킴

	glPopMatrix();
	glutSwapBuffers();

}

void MyReshape(int w, int h) { // 윈도우 크기를 조정해도 물체가 왜곡되지않음
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 조정한 윈도우 전체를 뷰폿으로 지정
	GLfloat WidthFactor = (GLfloat)w / (GLfloat)500;
	GLfloat HeightFactor = (GLfloat)h / (GLfloat)500;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-7 * WidthFactor, 7 * WidthFactor, -4 * HeightFactor, 7 * HeightFactor, -8, 8);
}

int main(int argc, char** argv) {

	Width = 500; // 윈도우의 가로(뷰폿변환사용을 위해 변수로 지정)
	Height = 500; // 윈도우의 세로(뷰폿변환사용을 위해 변수로 지정)
	glutInit(&argc, argv);
	// 은면제거를 위해 Z버퍼 사용준비, 자연스러운 애니메이션 효과를 위한 이중버퍼사용
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(Width, Height); // 윈도우 사이즈
	glutInitWindowPosition(100, 100); // 윈도우의 위치
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu); 
	// 실행직후, 키보드 인식을 위해 메뉴만들기를 여기에 두었음
	glutCreateWindow("HW#8");
	glutDisplayFunc(MyDisplay); // 콜백함수 등록
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecial);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(55, MyTimer2, 1); // 지속적으로 눈이 내리는 효과를 위한 타이머
	MyInit(); // 가시성판단, 은면제거, 조명을 위한 기본설정
	glutMainLoop();
	return 0;
}