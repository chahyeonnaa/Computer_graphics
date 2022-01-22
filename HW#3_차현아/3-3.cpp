/***********************************************************************/
/*                 HW#3-3 : Mouse Callback 응용                        */
/*  작성자 : 차현아                           날짜 : 2021년 10월 1일   */
/*                                                                     */
/* 문제 정의 : 알맞은 결과가 도출되도록 코드 5-3 수정                  */
/*                                                                     */
/* 기능 : 마우스 버튼을 통해 물체 조작하기                             */
/*        왼쪽버튼 클릭 -> 오른쪽으로 0.1씩 연속적으로 이동            */
/*        오른쪽 버튼 클릭 -> 이동중인 물체 멈춤                       */
/*        사각형이 윈도우의 경계에 도달하면 멈춤                       */
/***********************************************************************/
#include <GL/glut.h>

float Delta = 0.0; // 물체를 이동시키기위해 필요한 변수

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON); // 사각형 그리기
    glColor3f(1.0, 0.0, 0.0);

    if (0.0 + Delta >= 1) // 물체가 윈도우 영역을 벗어나지 않게 하기 위해서 사각형의 꼭짓점 중 하나의 x좌표가 1을 넘어가면
        glutIdleFunc(NULL); // 아이들 콜백을 멈추게 하였음

    glVertex3f(-1.0 + Delta, -0.5, 0.0); // 오른쪽 이동만 하면 되므로 x좌표에만 변수를 더해주면됨
    glVertex3f(0.0 + Delta, -0.5, 0.0); 
    glVertex3f(0.0 + Delta, 0.5, 0.0); 
    glVertex3f(-1.0 + Delta, 0.5, 0.0);
    glEnd();

    glutSwapBuffers(); // 애니메이션 효과를 위해 더블버퍼를 사용하였으므로 버퍼를 교차시켜주는 과정이 필요함
}

void MyIdle() {  // 오른쪽으로 0.0005씩 이동하도록 설정하였음.
                 // 문제에 정의된 0.1씩 하니까 너무 빠르게 지나가서 보기 편하기 위해서
    Delta = Delta + 0.0005;

    glutPostRedisplay(); // Display 콜백 함수 인위적 호출
}
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)
{
    if (State == GLUT_DOWN) // 버튼이 눌림
    {
        switch (Button) {
        case GLUT_LEFT_BUTTON: // 왼쪽 버튼이 눌리면
            glutIdleFunc(MyIdle); // 아이들 함수 호출 -> 아무일도 일어나지 않는 상태로 폴리곤이 움직이도록
                                  // 그래픽 기본요소를 계속 생성
            break;
        case GLUT_RIGHT_BUTTON: // 오른쪽 버튼 눌리면
            glutIdleFunc(NULL); // 아이들 콜백 멈춤(다시 왼쪽을 누르면 폴리곤이 움직임)
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
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // 더블버퍼링 사용
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Mouse Callback");
    MyInit();
    glutDisplayFunc(MyDisplay); 
    glutMouseFunc(MyMouseClick); // 마우스콜백 등록

    glutMainLoop();
    return 0;
}