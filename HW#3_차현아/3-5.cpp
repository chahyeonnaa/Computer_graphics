/***********************************************************************/
/*                 HW#3-5 : Idle Callback 응용                         */
/*  작성자 : 차현아                           날짜 : 2021년 10월 1일   */
/*                                                                     */
/* 문제 정의 : 알맞은 결과가 도출되도록 코드 5-7 수정                  */
/*                                                                     */
/* 기능 : 방향키를 누르면,                                             */
/*        방향키 방향대로 폴리곤이 연속적으로 움직이게함               */
/*        모든 좌표는 윈도우 영역을 벗어나지 않으며,                   */
/*        폴리곤이 경계에 도달하면 멈춘 뒤, 다시 방향키를 조작하면     */
/*        해당 방향으로 다시 움직이도록 설계하였음                     */
/***********************************************************************/
#include <GL/glut.h>

float Delta = 0.0; // y축 이동을 위한 변수(위, 아래)
float Seta = 0.0; // x축 이동을 위한 변수(오른쪽, 왼쪽이동)

// 각 좌표들을 이동하고자하는 방향으로 0.0005만큼씩 이동시키면, 물체 전체가 이동함.
// 0.1씩 이동은 너무 빠르기때문에 편의를 위해 0.0005로 조정
void MyIdle() { // 위
    Delta = Delta + 0.0005;

    glutPostRedisplay(); // Display콜백 함수를 인위적으로 호출시킴
}

void MyIdle2() { // 아래
    Delta = Delta - 0.0005;

    glutPostRedisplay(); // Display콜백 함수를 인위적으로 호출시킴
}

void MyIdle3() { // 왼
    Seta = Seta - 0.0005;

    glutPostRedisplay(); // Display콜백 함수를 인위적으로 호출시킴
}

void MyIdle4() { // 오른쪽
    Seta = Seta + 0.0005;

    glutPostRedisplay(); // Display콜백 함수를 인위적으로 호출시킴
}
void MyDisplay() {

    // 사각형이 윈도우의 경계에 도달했을 때 아이들 함수를 멈춰야 윈도우 영역을 벗어나지않음
    // 사각형의 각 좌표들의 위치를 제한을 두어 아이들 콜백을 멈춰서 못벗어나게 하였음 
    if (0.5 + Delta >= 1 || 0.5 + Seta >= 1 || -0.5 + Delta <= -1 || -0.5 + Seta <= -1)
    {
        glutIdleFunc(NULL);
        // 경계에서 멈추고, 다시 키를 누르면 사각형이 움직이게 하기 위해서 아이들 콜백을 멈춘 뒤
        // 좌표들을 수정하여 위의 if문에 걸리지 않도록 하였음
        // 좌표 수정은 더해지거나 빼진 0.0005를 취소시켰음
        if(0.5 + Delta>=1) // 위쪽
            Delta = Delta - 0.0005;
        else if(-0.5 + Delta<=-1) // 아래쪽
            Delta = Delta + 0.0005;
        else if (0.5 + Seta >= 1) // 오른쪽
            Seta = Seta - 0.0005;
        else if (-0.5 + Seta <= -1) // 왼쪽
            Seta = Seta + 0.0005;
    }


    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON); // 사각형 그리기
    glColor3f(1.0, 0.0, 0.8); // 핑크색으로 그리기
    glVertex3f(-0.5 + Seta, -0.5 + Delta, 0.0); 
    glVertex3f(0.5 + Seta, -0.5 + Delta, 0.0); 
    glVertex3f(0.5 + Seta, 0.5 + Delta, 0.0); 
    glVertex3f(-0.5 + Seta, 0.5 + Delta, 0.0); 
    glEnd();
    glutSwapBuffers(); // 애니메이션 효과를 위해 이중버퍼를 사용하였으므로 버퍼교체과정 필요
}

void MySpecial(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP: // 위쪽 키를 누르면
         glutIdleFunc(MyIdle); // 물체가 위로올라감
         break;
    case GLUT_KEY_DOWN: // 다운키를 누르면
         glutIdleFunc(MyIdle2); // 내려감
         break;
    case GLUT_KEY_LEFT: // 왼쪽키 누르면
         glutIdleFunc(MyIdle3); // 왼쪽이동
         break;
    case GLUT_KEY_RIGHT: // 오른쪽 누르면
         glutIdleFunc(MyIdle4); // 오른쪽 이동
         break;

    default:
        break;
    }

    glutPostRedisplay();
}

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // 애니메이션 효과를 위해 더블버퍼 사용
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Idle Callback");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutSpecialFunc(MySpecial); // 스페셜 키보드 콜백 등록(문자 아닌 것들을 누를때)

    glutMainLoop();
    return 0;
}