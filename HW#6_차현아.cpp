/***********************************************************************/
/*                 HW#6-1 : 뷰폿 변환 이해                             */
/*  작성자 : 차현아                           날짜 : 2021년 11월 5일   */
/*                                                                     */
/* 문제 정의 : 코드 7-2 수정하여 아래 기능에 맞게 구현                 */
/*                                                                     */
/* 기능 : 하나의 윈도우를 4개의 뷰폿으로 분할(뷰폿 하나당 물체 2개)    */
/*        우상단 뷰폿: 원근투영 / 좌하단 뷰폿: 평행투영                */
/*        키보드 콜백을 이용하여 시점변환이 수행됨                     */
/*        2- 우상단, 3- 좌하단                                         */
/* 시점변환을 하고 싶은 뷰폿 번호를 위를 참고하여 키보드로 입력한 뒤, 오른쪽 왼쪽 방향키로 제어가능 */
/* ex) 좌하단 뷰폿을 시점변환 하고싶으면, 3을 입력한뒤 방향키로 제어   */
/*  2,3 번갈아가면서 선택해도 각 뷰폿을 자유롭게 시점변환 가능         */
/*    윈도우 크기 조절 시 크기에 상관없이 객체의 형태가 왜곡되지 않음  */
/***********************************************************************/
#include <GL/glut.h>
int kase = 0; // 뷰폿선택 변수
int Width, Height; // 윈도우 크기
float x2 = 0, y2 = 0;
float x3 = 0, y3 = 0;

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawScene() { // 바닥이랑 주전자그리기
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    glTranslatef(0.0, -1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(2.0, 0.0, 2.0);
    glVertex3f(2.0, 0.0, -2.0);
    glVertex3f(-2.0, 0.0, -2.0);
    glVertex3f(-2.0, 0.0, 2.0);
    glEnd();
    glPopMatrix();

    glColor3f(1.0, 0.2, 0.5);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    glutWireTeapot(1.0);
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    //좌하단
    glViewport(0, 0, Width / 2, Height / 2); // 뷰폿나누기_윈도우의 좌하단부분
    // 좌하단 영역에만 그림을 그린다
    glMatrixMode(GL_PROJECTION); // 투영행렬스택
    glLoadIdentity(); // 항등행렬로 초기화
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0); // 평행투영
    glPushMatrix(); // 평행투영한 값 행렬스택에 저장

    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬스택
    glLoadIdentity(); // 항등행렬로 초기화
    glPushMatrix();
    gluLookAt(0.0 + x3, 1.0 + y3, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 시점변환
    // kase 값이 3이면, x3 y3변수가 방향키 조작에 따라 조절됨
    DrawScene();

    // 토러스 그리기
    glColor3f(0.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.0);
    glutWireTorus(0.3, 0.5, 20, 20);
    glPopMatrix();
    glPopMatrix();

    // 우상단
    glViewport(Width / 2, Height / 2, Width / 2, Height / 2); // 뷰폿나누기_윈도우의 우상단부분
    // 우상단영역에만 그림을 그린다.
    glMatrixMode(GL_PROJECTION); // 투영행렬스택
    glLoadIdentity(); // 항등행렬로 초기화
    glPushMatrix(); // 저장

    gluPerspective(130, 1.0, 2.0, 0.0); // 원근투영_ 객체가 잘 보일수있도록 인자값 조절
    // 멀리있는건 멀리, 가까이있는 것은 가까이보임

    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬스택
    glLoadIdentity();
    glPushMatrix();
    gluLookAt(0.0 + x2, 0.0 + y2, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 시점변환
    // kase 값이 2이면, x2 y2변수가 방향키 조작에 따라 조절됨
    DrawScene();

    // 토러스 그리기
    glColor3f(0.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.0);
    glutWireTorus(0.3, 0.5, 20, 20);
    glPopMatrix();
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();
}
void MyReshape(int NewWidth, int NewHeight) // 윈도우 크기 조절 시 왜곡을 막아주는 함수
{
    glViewport(0, 0, NewWidth, NewHeight); // 조정되는 윈도우 전체를 뷰폿으로 지정
    GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500;
    GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0 * Widthfactor, 2.0 * Widthfactor, -2.0 * Heightfactor, 2.0 * Heightfactor, 0.5, 5.0);

}
void MyKeyboard(unsigned char key, int x, int y) { // 시점변환을 할 뷰폿선택
    switch (key) {
    case '3': // 좌하단 선택
        kase = 3;
        break;
    case '2': // 우상단 선택
        kase = 2;
        break;
    }
    glutPostRedisplay();
}
void MySpecial(int key, int x, int y) { // 오른쪽, 왼쪽 방향키로 시점 조절
    switch (key) {
    case GLUT_KEY_RIGHT: // kase값에 따라 시점변환 변수가 조절된다
        if (kase == 3)
        {
            x3 = x3 + 0.1;
            y3 = y3 + 0.1;
        }
        else if (kase == 2)
        {
            x2 = x2 + 0.1;
            y2 = y2 + 0.1;
        }
        break;
    case GLUT_KEY_LEFT:
        if (kase == 3)
        {
            x3 = x3 - 0.1;
            y3 = y3 - 0.1;
        }

        if (kase == 2)
        {
            x2 = x2 - 0.1;
            y2 = y2 - 0.1;
        }

        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    Width = 500;
    Height = 500;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Viewpory Partition");
    MyInit();
    glutDisplayFunc(MyDisplay); // 콜백함수 등록
    glutKeyboardFunc(MyKeyboard);
    glutReshapeFunc(MyReshape);
    glutSpecialFunc(MySpecial);
    glutMainLoop();
    return 0;
}