/***********************************************************************/
/*                 HW#3-1 : Keyboard Callback 응용(1)                  */
/*  작성자 : 차현아                           날짜 : 2021년 10월 1일   */
/*                                                                     */
/* 문제 정의 :  알맞은 결과가 도출되도록 코드 5-3 수정                 */
/*                                                                     */
/* 기능 : a,f,r,v,b를 조작하여 정해진 결과 도출                        */
/*        a - 왼쪽이동, f - 오른쪽이동, r- 아래쪽 이동, 색변환         */
/*        v - 위쪽 이동, b - 색변환                                    */
/***********************************************************************/
#include <GL/glut.h>

float Delta = 0.0; // x축이동과 관련된 변수(왼쪽 오른쪽)
float Seta = 0.0; // y축이동과 관련된 변수(아래 위)
unsigned char pwd; // 키보드 입력값(key)을 받아서 함수 밖에서도 key값을 기억하기 위한 변수

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (pwd == 'B' || pwd == 'b') // 받아온 key값이 b이면(사용자가 B를 누르면)
        glColor3f(0.0, 0.0, 1.0); // 파란색으로 칠하기
    else if (pwd == 'R' || pwd == 'r') // 받아온 key값이 r이면(사용자가 R를 누르면)
        glColor3f(1.0, 0.0, 0.0); // 빨간색으로 칠하기
    else
        glColor3f(0.5, 0.5, 0.5); // 그외이면 색을 변환하지 않으므로 그대로 유지

    glBegin(GL_POLYGON); // 사각형그리기 - 사각형 전체가 이동해야하므로 전체좌표를 이동시켜야함
                         // x축 이동이면, x좌표들에 Delta가 더해지고 y축 이동이면, y좌표에 Seta가 더해짐
    glVertex3f(-0.5 + Delta, -0.5 + Seta, 0.0); // 
    glVertex3f(0.5 + Delta, -0.5 + Seta, 0.0); //
    glVertex3f(0.5 + Delta, 0.5 + Seta, 0.0); //
    glVertex3f(-0.5 + Delta, 0.5 + Seta, 0.0); //
    glEnd();
    glFlush();
}

void MyKeyboard(unsigned char key, int x, int y) {

    pwd = key; // key값을 받아서 함수 밖에서도 key값을 기억하기 위한 변수

    switch (key) {
    case 'A':
    case 'a': // a를 누르면
        Delta = Delta - 0.1; // 왼쪽으로 이동
        break;
    case 'F':
    case 'f': // f를 누르면
        Delta = Delta + 0.1; // 오른쪽으로 이동
        break;
    case 'R':
    case 'r': // r을 누르면
        Seta = Seta - 0.1; // 아래쪽 이동
        break;
    case 'V':
    case 'v': // v를 누르면
        Seta = Seta + 0.1; // 위쪽으로 이동
        break;
    case 'B':
    case 'b':
        break;
    }
    glutPostRedisplay(); // Display콜백을 인위적으로 발생시키기위한 함수
}


void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300); // 윈도우사이즈
    glutInitWindowPosition(30, 30); // 윈도우가 뜨는 위치
    glutCreateWindow("Keyboard Callback 3-1");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);// 키보드 콜백 등록

    glutMainLoop();
    return 0;
}