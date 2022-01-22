/***********************************************************************/
/*                 HW#1 : 3D Sierpinski Gasket                         */
/*  작성자 : 차현아                           날짜 : 2021년 9월 17일   */
/*                                                                     */
/* 문제 정의 : 2D triangle Gasket을 3D tetrahedron Gasket으로 변경하기 */
/*                                                                     */
/* 기능 : 정사면체구현 - glEnable(GL_DEPTH_TEST),glRotatef()           */
/*        Reshape Callback을 이용하여 왜곡문제 해결                    */
/*                                                                     */
/***********************************************************************/
#include <GL/glut.h>
#include <stdlib.h>
int num = 3; // * 코드를 이해하기 위해 알아야하는 점 : 우리가 그릴 정사면체는 총 4개의 큰 정사면체로 이루어짐.
			 // 각 사면체 하나 당 몇개의 사면체로 구성할 것인지 결정하는 변수
			 // ex) num이 3이면, 일차원적으로 봤을 때 사면체 한면당 27개의 삼각형으로 구성됨
			 // 사면체를 더 잘잘하게 분할하려면, num값을 증가시켜주면 됨
void draw(GLfloat* qa, GLfloat* qb, GLfloat* qc) // (사면체를 이루는 한 면 ==)하나의 삼각형을 그리는 과정
{
	glVertex3fv(qa);
	glVertex3fv(qb);
	glVertex3fv(qc);
}
void beforedraw(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d)// 각 포인터는 2차원 배열의 전체 행을 받음
// searchmid 에서 결정된 정점들을 연결하여 draw함수에서 삼각형을 그림 -> beforedraw()에서 사면체가 완성됨
// 배열의 이름(배열의 주솟값을 가짐) == 포인터
// 각 포인터들은 x,y,z 위치 값을 가지는 1차원 배열
{
	glColor3f(0.0, 1.0, 1.0); // 하늘색
	draw(a, b, c); // 각 정점들을 찍어 삼각형을 만듦
	glColor3f(1.0, 0.0, 0.0); // 빨간색
	draw(a, c, d);
	glColor3f(0.0, 0.0, 1.0); // 파란색
	draw(a, d, b);
	glColor3f(1.0, 1.0, 0.0); // 노란색(시야에 보이지 않는 면)- glRotatef()통해 회전시키면 볼 수 있음
	draw(b, d, c);
}

void searchmid(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d, int m)
{
	GLfloat mid[6][3]; // 사면체에 존재하는 모든 변들의 중점의 위치를 담을 배열
					   // 변의 갯수가 6개이고, 3차원 도형이기 때문에, 2차원 배열 6열 3행으로 구성하였음. 
	int j;
	if (m > 0) // (num==m)은 정사면체를 이루는 각 사면체들을 몇개의 사면체로 분할 할 것인지 결정해줌
			   // 1번 분할하면 사면체가 4개로 쪼개지고, 2번분할시-16개, 3번분할시-256개로 분할됨
			   // 그에따라 각변의 중점을 찾아주는 함수 searchmid의 호출 횟수도 결정됨
	{
		for (j = 0; j < 3; j++) mid[0][j] = (a[j] + b[j]) / 2; // 각변의 x,y,z 좌표의 중점을 구함
		for (j = 0; j < 3; j++) mid[1][j] = (a[j] + c[j]) / 2; // 6개의 변이므로 6개의 중점이 나옴
		for (j = 0; j < 3; j++) mid[2][j] = (a[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) mid[3][j] = (b[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) mid[4][j] = (b[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) mid[5][j] = (c[j] + d[j]) / 2;
		searchmid(a, mid[0], mid[1], mid[2], m - 1); // 위의 반복문에서 구한 중점들을 사면체의 vertex로 하여 함수 재호출
		searchmid(mid[0], b, mid[3], mid[4], m - 1); // m의 조건에 따라 함수가 재호출되거나, 삼각형을 그리러감
		searchmid(mid[1], mid[3], c, mid[5], m - 1);
		searchmid(mid[2], mid[4], mid[5], d, m - 1);
		// 사면체 하나를 4개의 4면체로 분할가능
	}
	else // num번 만큼의 중점분할이 끝났으면, 점 찍어주는 함수 호출
		beforedraw(a, b, c, d); // 결정된 4개의 vertex들을 이용하여 사면체를 이루는 삼각형을 그리면 하나의 사면체가 완성됨 
}

void MyDisplay(void)
{
	float vertices[4][3] = { {0.0,0.0,50.0},{0.0,50.0,0.0},{-50.0,-25.0,0.0}, {50.0,-25.0,0.0} }; // 초기사면체 생성
	// 설정한 가시부피에 사면체가 들어오도록 사면체의 정점을 잡음
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 버퍼 지우기
	// 우리는 3차원 물체(정사면체)를 그릴 것이기 때문에 깊이버퍼를 두어서 픽셀별로 깊이값을 저장시킴.
	glBegin(GL_TRIANGLES); // 세 정점들이 연결되는 삼각형을 그리기 시작
	searchmid(vertices[0], vertices[1], vertices[2], vertices[3], num);
	// 초기 사면체에서부터 존재하는 모든 변의 중점을 찾고, 점을 찍어주는 함수
	// num의 값에 따라 반복 횟수가 달라지게됨
	// 2차원 배열이므로 함수의 매개변수를 포인터로 받음
	glEnd(); // 도형 정의 끝
	glFlush(); // 현재까지 쌓인 명령어를 모두 프로세서에게 전달하라는 명령
}
void MyReshape(int NewWidth, int NewHeight) // 왜곡문제 해결함수(매개변수는 os가 알려주는 조정된 새로운 윈도우의 크기)
{
	glViewport(0, 0, NewWidth, NewHeight); // 조정된 윈도우 전체를 뷰폿으로 지정
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500; // 조정된 비율을 알기위해 초기 윈도우 크기를 새로운 값들로 나누어줌
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500; // -> 위에서 결정된 비율만큼 가시부피를 바꾸어야함
	glMatrixMode(GL_PROJECTION); // 가시부피를 바꿔주기 위해 투영행렬을 쓰겠다고 지정
	glLoadIdentity();
	glOrtho(-100.0 * Widthfactor, 100.0 * Widthfactor, -100.0 * Heightfactor, 100.0 * Heightfactor, -500.0, 500.0);
	// depth는 그대로두고, 조정된 크기의 비율만큼 기존 값들에 곱해줌 -> 가시부피 조정
	// left, right, bottom, top, -near, -far순서로 가시부피 설정
}
void Myinit()
{
	glEnable(GL_DEPTH_TEST); // depth test는 기본적으로 비활성화 되어있음
	// 우리는 3차원 물체(정사면체)를 그릴 것이기 때문에 3차원 값을 처리하는 깊이버퍼를 두어서 픽셀별로 깊이값을 저장시킴.
	// -> 3차원 물체 표현가능
	glClearColor(1.0, 1.0, 1.0, 1.0); // 윈도우 배경색상을 흰색으로 지정
	// 입체감을 더하기 위하여 사면체를 회전시킴
	glRotatef(10.0, 1.0, 0.0, 0.0); // x축을 중심으로 10도 회전
	glRotatef(20.0, 0.0, 1.0, 0.0); // y축을 중심으로 20도 회전
	glRotatef(10.0, 0.0, 0.0, 1.0); // z축을 중심으로 10도 회전
}
int main(int argc, char** argv) // 윈도우화면 초기화 및 콜백함수 등록
{
	glutInit(&argc, argv); //glut 초기화
	glutInitDisplayMode(GLUT_RGB);// 윈도우 디스플레이모드 설정 함수
	glutInitWindowSize(500, 500);// 윈도우 크기설정
	glutInitWindowPosition(0, 0);// 윈도우 위치설정
	glutCreateWindow("Sierpinski Gasket");// 새로운 윈도우 생성

	Myinit(); // main함수에는 윈도우 초기화 및 콜백함수를 등록해야하는 암묵적인 룰에 따라 함수를 따로 만들어
			  // gl을 사용하기 위한 공간을 따로 마련하였음
	glutDisplayFunc(MyDisplay); //콜백함수 등록
	glutReshapeFunc(MyReshape); //콜백함수 등록
	glutMainLoop(); // 이벤트 처리루프_이벤트 발생 시 그에 맞는 콜백함수 호출
	return 0;
}