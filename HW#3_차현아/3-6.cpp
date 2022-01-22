/***********************************************************************/
/*                 HW#3-6 : Timer Callback 응용                        */
/*  작성자 : 차현아                           날짜 : 2021년 10월 1일   */
/*                                                                     */
/* 문제 정의 : 알맞은 결과가 도출되도록 코드 5-8 수정                  */
/*                                                                     */
/* 기능 : 프로그램 실행 시 도형을 오른쪽으로 연속적으로 움직이게하기   */
/*        오른쪽 경계에 부딪히면 색이 바뀌면서 왼쪽으로 서서히 이동    */
/*        마우스 왼쪽 버튼 클릭 -> 이동중인 물체 멈춤                  */
/***********************************************************************/
#include <GL/glut.h>
void MyTimer1(int);
void MyTimer2(int);
// 타이머 호출 간격과 이동거리를 보기좋게 적당히 조절하였음
GLfloat Delta = 0.0; // 물체 이동을 위한 변수
int Case = 0; // 각 타이머마다 마우스 왼쪽 버튼 눌림을 알려주는 변수(마우스 함수에서 받아옴)

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON); // 사각형그리기
    glVertex3f(-1.0 + Delta, -0.5, 0.0);
    glVertex3f(0.0 + Delta, -0.5, 0.0);
    glVertex3f(0.0 + Delta, 0.5, 0.0);
    glVertex3f(-1.0 + Delta, 0.5, 0.0);
    glEnd();
    glutSwapBuffers(); // 애니메이션 효과를 위해 이중버퍼를 사용했으므로 버퍼교체과정 필요
}
void MyTimer2(int Value) { // 왼쪽 이동 타이머

    glColor3f(0.0, 0.0, 1.0); // 파란색으로 색 바꿈
    glutPostRedisplay(); // 인위적으로 Display 콜백 발생시키기
    Delta = Delta - 0.05; // 왼쪽 이동

    if (Case == 1) // 왼쪽 버튼 눌리면 함수 종료
        return;

    if (-1.0 + Delta <= -1.0) // 물체가 윈도우 왼쪽 경계에 도달하면
        glutTimerFunc(40, MyTimer1, 1); // 다시 오른쪽으로 이동, 타이머1 호출
    else
        glutTimerFunc(40, MyTimer2, 1); // glut 타이머는 함수가 등록되면 단 한번만 이벤트를 발생시키므로
                                        // 인위적으로 타이머이벤트를 발생시켜주어야함
}

void MyTimer1(int Value) { // 오른쪽 이동 타이머

    glColor3f(1.0, 0.0, 0.6); // 핑크색으로 그리기 
    glutPostRedisplay(); // 인위적으로 Display 콜백 발생시키기
    Delta = Delta + 0.05; // 오른쪽으로 0.05씩 이동

    if (Case == 1) // 멈춤 버튼 클릭
        return; // 타이머 함수 종료시키기

    if (Delta >= 1.0) // 물체가 윈도우 오른쪽 경계에 도달하면
    {
        glutTimerFunc(40, MyTimer2, 1); // 다시 왼쪽으로 이동함, 타이머2 호출(물체의 색 바뀜)
    }
    else // 그렇지않으면 타이머1 호출
        glutTimerFunc(40, MyTimer1, 1); // glut 타이머는 함수가 등록되면 단 한번만 이벤트를 발생시키므로
                                        // 인위적으로 타이머이벤트를 발생시켜주어야함
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)
{
    if (State == GLUT_DOWN)
    {
        switch (Button) {
        case GLUT_LEFT_BUTTON: // 왼쪽 버튼이 눌리면
            Case = 1; // Case값을 1로 세팅
            break;
        case GLUT_RIGHT_BUTTON: // 오른쪽 버튼을 누르면
            Case = 2; // Case 값을 2로 세팅
            break;
        }
    }
}
void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // 애니메이션 효과를 위해 이중버퍼 사용
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Timer Callback");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutTimerFunc(40, MyTimer1, 1); // 타이머 콜백함수 등록 (40msec마다 호출)
    glutMouseFunc(MyMouseClick); // 마우스 콜백 등록

    glutMainLoop();
    return 0;
}