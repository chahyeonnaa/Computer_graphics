/***********************************************************************/
/*                 HW#3-2 : Keyboard Callback 응용                     */
/*  작성자 : 차현아                           날짜 : 2021년 10월 1일   */
/*                                                                     */
/* 문제 정의 : 알맞은 결과가 도출되도록 코드 5-3 수정                  */
/*                                                                     */
/* 기능 : 방향키를 누르면,                                             */
/*        방향키 방향대로 폴리곤이 0.1씩 움직이게함                    */
/*        모든 좌표는 윈도우 영역을 벗어나지 않으며,                   */
/*        PageUp 버튼을 누르면, 폴리곤이 0.1씩 확대                    */
/*        PageDown 버튼을 누르면, 폴리곤이 0.1씩 축소                  */
/*        사각형의 확대는 가시적으로 보이는 공간까지 일어나게 하였고,  */
/*        확대과정에서 한 면이라도 윈도우 경계와 맞닿으면 확대가 진행되지 않도록 하였음 */
/*        사각형의 위치를 조정할 때 사각형이 윈도우와 맞닿으면, 초기자리로 돌아오도록 설계하였음 */
/*        사각형의 축소는 시각적으로 최소일때 더이상 축소되지 않도록 하였음 */
/*        하지만 초기 상태에서 최대한으로 축소 -> 최대한으로 확대 -> 다시 최소한으로 축소 과정을 반복하면*/
/*        최대한으로 축소하였을 때 사각형이 사라지는 문제가 발생함                         */
/*        기본적인 확대, 축소는 정상적으로 작동함                      */
/***********************************************************************/

#include <GL/glut.h>
float Delta = 0.0; // x축 이동(오른쪽 왼쪽)
float Seta = 0.0; // y축 이동(위 아래)
float Zoomin = 0.0; // 확대
float Zoomout = 0.0; // 축소

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);

    glBegin(GL_POLYGON);
    // 확대, 축소, 도형 움직임이 동시에 일어날 수 있도록 하였음
    glVertex3f(-0.5 - Zoomin + Zoomout + Delta, -0.5 - Zoomin + Zoomout + Seta, 0.0); //1
    glVertex3f(0.5 + Zoomin - Zoomout + Delta, -0.5 - Zoomin + Zoomout + Seta, 0.0); //2
    glVertex3f(0.5 + Zoomin - Zoomout + Delta, 0.5 + Zoomin - Zoomout + Seta, 0.0); //3
    glVertex3f(-0.5 - Zoomin + Zoomout + Delta, 0.5 + Zoomin - Zoomout + Seta, 0.0); //4
    glEnd();
    glFlush();
}

void MySpecial(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP: // 윗방향 키를 누르면,
        if (0.5 + Zoomin - Zoomout + Seta >= 1) // 좌표가 윈도우 경계와 맞닿으면
        {
            Seta = 0; // 더 이상 나아가지 못하고 윈도우의 중심으로 이동
            break;
        }
        else
        {
            Seta = Seta + 0.1; // 0.1씩 위로 이동
            break;
        }
    case GLUT_KEY_DOWN: // 아래 방향키를 누르면
        if (-0.5 - Zoomin + Zoomout + Seta <= -1) // 좌표가 윈도우 경계와 맞닿으면
        {
            Seta = 0; // 더 이상 나아가지 못하고 윈도우의 중심으로 이동
            break;
        }
        else
        {
            Seta = Seta - 0.1; // 0.1씩 아래로 이동
            break;
        }
    case GLUT_KEY_LEFT: // 좌측 방향키를 누르면
        if (-0.5 - Zoomin + Zoomout + Delta <= -1) // 좌표가 윈도우 경계와 맞닿으면
        {
            Delta = 0; // 더 이상 나아가지 못하고 윈도우의 중심으로 이동
            break;
        }
        else
        {
            Delta = Delta - 0.1; // 0.1씩 왼쪽으로 이동
            break;
        }
    case GLUT_KEY_RIGHT: // 우측 방향키를 누르면
        if (0.5 + Zoomin - Zoomout + Delta >= 1) // 좌표가 윈도우 경계와 맞닿으면
        {
            Delta = 0; // 더 이상 나아가지 못하고 윈도우의 중심으로 이동
            break;
        }
        else
        {
            Delta = Delta + 0.1; // 0.1씩 오른쪽으로 이동
            break;
        }
    case GLUT_KEY_PAGE_DOWN: // 축소
        // 가시적으로 최소일때 사각형의 넓이 : 0.01 
        if (((0.5 + Zoomin - Zoomout + Delta) - (-0.5 - Zoomin + Zoomout + Delta)) * ((0.5 + Zoomin - Zoomout + Delta) - (-0.5 - Zoomin + Zoomout + Delta)) < 0.01)
            // 최소 넓이에 도달하면 더 이상 축소되지 않도록 하였음
            break;
        else
        {
            Zoomout = Zoomout + 0.05; // 0.1 씩 축소해야하니까 각 좌표들은 0.05씩 감소/증가
            break;
        }
    case GLUT_KEY_PAGE_UP: // 확대
        if (-0.5 - Zoomin + Zoomout + Delta <= -1 || -0.5 - Zoomin + Zoomout + Seta <= -1 ||
            0.5 + Zoomin - Zoomout + Delta >= 1 || -0.5 - Zoomin + Zoomout + Seta <= -1 ||
            0.5 + Zoomin - Zoomout + Delta >= 1 || 0.5 + Zoomin - Zoomout + Seta >= 1 ||
            -0.5 - Zoomin + Zoomout + Delta <= -1 || 0.5 + Zoomin - Zoomout + Seta >= 1)
            // 사각형의 모든 좌표들이 하나라도 윈도우 경계와 맞닿으면 확대되지 않도록 하였음
            break;
        else
        {
            Zoomin = Zoomin + 0.05; // 0.1 씩 축소해야하니까 각 좌표들은 0.05씩 감소/증가
            break;
        }

    default:
        break;
    }
    glutPostRedisplay(); // 디스플레이 콜백 함수 인위적 호출
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
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Keyboard Callback");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutSpecialFunc(MySpecial);

    glutMainLoop();
    return 0;
}