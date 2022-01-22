/***********************************************************************/
/*                 HW#3-4 : Menu Callback 응용                         */
/*  작성자 : 차현아                           날짜 : 2021년 10월 1일   */
/*                                                                     */
/* 문제 정의 : 알맞은 결과가 도출되도록 코드 5-6 수정                  */
/*                                                                     */
/* 기능 : 주메뉴 : Draw Sphere, Draw Torus, Draw Teapot, Change Color, Exit */
/*       Draw Sphere 하부 메뉴 : Small Sphere, Large Sphere            */
/*        Draw Torus 하부 메뉴 : Small Torus , Large Torus             */
/*        Draw Teapot 하부 메뉴 : Small Teapot , Large Teapot          */
/*        Change Color 하부 메뉴 : Red, Green, Blue                    */
/***********************************************************************/
#include <GL/glut.h>

float r = 0.0;
float g = 0.0;
float b = 0.0;// 색깔 구분(디폴트 검정)

// 메뉴콜백 함수에서 아이디 값마다 draw값을 할당하여 MyDisplay()로 전달하여 그림을 그린다.
int draw = 1; // 각 모형들을 그리기 위한 변수, 할당되는 숫자들로 모형들을 구분함

void MyDisplay() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    switch (draw) {
    case 1: // 큰 구
        glColor3f(r, g, b);
        glutWireSphere(0.7, 30, 30);
        break;
    case 2: // 작은 구
        glColor3f(r, g, b);
        glutWireSphere(0.5, 30, 30);
        break;
    case 3: // 작은 토러스
        glColor3f(r, g, b);
        glutWireTorus(0.1, 0.3, 40, 20);
        break;
    case 4: // 큰 토러스
        glColor3f(r, g, b);
        glutWireTorus(0.2, 0.5, 40, 20);
        break;
    case 5: // 작은 주전자
        glColor3f(r, g, b);
        glutWireTeapot(0.35);
        break;
    case 6: // 큰 주전자
        glColor3f(r, g, b);
        glutWireTeapot(0.55);
        break;
    default:
        break;
    }

    glFlush();
}

void MySphereMenu(int entryID) { // 구 그리기
    if (entryID == 1)           draw = 1; // 큰구
    else if (entryID == 2)      draw = 2; // 작은구 그리기

    glutPostRedisplay();
}

void MyTorusMenu(int entryID) { // 토러스 그리기
    if (entryID == 1)           draw = 3; // 작은거
    else if (entryID == 2)      draw = 4; // 큰거

    glutPostRedisplay();
}

void MyTeapotMenu(int entryID) { // 주전자 그리기
    if (entryID == 1)           draw = 5; // 작은거
    else if (entryID == 2)      draw = 6; // 큰거

    glutPostRedisplay();
}

void MyColorMenu(int entryID) {
    if (entryID == 1) // 메뉴생성시 할당된 번호가 1인 항목을 클릭하면
        r = 1.0, g = 0.0, b = 0.0; // 레드
    else if (entryID == 2) // 메뉴생성시 할당된 번호가 1인 항목을 클릭하면
        r = 0.0, g = 1.0, b = 0.0; // 그린
    else if (entryID == 3) // 메뉴생성시 할당된 번호가 1인 항목을 클릭하면
        r = 0.0, g = 0.0, b = 1.0; // 블루
    glutPostRedisplay(); // 디스플레이 콜백함수 인위적으로 호출하기
}

void MyMainMenu(int entryID) { // 주메뉴
    if (entryID == 3)            exit(0); // 주메뉴에서 아이디값 3에 해당하는걸 누르면, 프로그램 종료

    glutPostRedisplay(); 
}

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    GLint Mysphere = glutCreateMenu(MySphereMenu); // 서브메뉴 생성
    glutAddMenuEntry("Large Sphere", 1); // 메뉴항목 첨가
    glutAddMenuEntry("Small Sphere", 2); // 숫자는 항목이 선택될때 메뉴콜백 함수에게 전달되는 정수값

    GLint Mytorus = glutCreateMenu(MyTorusMenu); // 서브메뉴 생성
    glutAddMenuEntry("Small Torus", 1); // 메뉴항목 첨가
    glutAddMenuEntry("Large Torus", 2);

    GLint Myteapot = glutCreateMenu(MyTeapotMenu); // 서브메뉴 생성
    glutAddMenuEntry("Small Teapot", 1); // 메뉴항목 첨가
    glutAddMenuEntry("Large Teapot", 2);

    GLint Mycolor = glutCreateMenu(MyColorMenu); // 서브메뉴 생성
    glutAddMenuEntry("Red", 1); // 메뉴항목 첨가
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu); // 주메뉴 생성(아이디 값 리턴)
    glutAddSubMenu("Draw Sphere", Mysphere); // 서브메뉴항목 추가_ 메뉴마다 별도의 콜백함수 등록해야함
    glutAddSubMenu("Draw Torus", Mytorus);
    glutAddSubMenu("Draw Teapot", Myteapot);
    glutAddSubMenu("Change Color", Mycolor);
    glutAddMenuEntry("Exit", 3); // 서브메뉴가 아닌 메뉴항목 추가(주메뉴에서 3번 할당)
    glutAttachMenu(GLUT_RIGHT_BUTTON); // 오른쪽 마우스 버튼에 메뉴 할당(오른쪽을 누르면 메뉴가 팝업)

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500, 500); // 윈도우사이즈
    glutInitWindowPosition(0, 0); // 윈도우 위치
    glutCreateWindow("Menu Callback");
    MyInit();

    glutDisplayFunc(MyDisplay); // 디스플레이 콜백함수 등록

    glutMainLoop();
    return 0;
}