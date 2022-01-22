/***********************************************************************/
/*                 HW#5-1 : gluLookAt()의 실시간 제어                  */
/*  작성자 : 차현아                           날짜 : 2021년 10월 29일  */
/*                                                                     */
/* 문제 정의 : 코드 6-8 수정                                           */
/*                                                                     */
/* 기능 : 방향키 조작에따라 Camera X,Y축의 좌표가 0.1씩 증가 혹은 감소 */
/*        A(a),F(f),R(r),V(v),Z(z),T(t)를 누름에따라 초점의 X,Y좌표가  */
/*        0.1씩 증가 혹은 감소                                         */
/***********************************************************************/
#include <GL/glut.h>
float Delta = 0; // 카메라 위치 조정변수
float Seta = 0; // 카메라 위치 조정변수
float FocusX = 0; // 초점 위치 조정변수
float FocusY = 0; // 초점 위치 조정변수
float FocusZ = 0; // 초점 위치 조정변수
void DrawGround() // 바닥그리기
{ 
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON); // 사각형 그리기(밑바닥)
    glVertex3f(-2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, -2.0);
    glVertex3f(-2.0, -0.71, -2.0);
    glEnd();

    glColor3f(0.3, 0.3, 0.3);

    glBegin(GL_LINES); // 밑바닥에 줄긋기
    for (float x = -2.0; x <= 2.2; x += 0.2) {
        glVertex3f(x, -0.7, -2.0);
        glVertex3f(x, -0.7, 2.0);
    }

    for (float z = -2.0; z <= 2.2; z += 0.2) {
        glVertex3f(-2.0, -0.7, z);
        glVertex3f(2.0, -0.7, z);
    }
    glEnd();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 뷰행렬이 만들어짐
    // 키를 조작함에따라 0.1만큼씩 카메라위치, 초점이 움직임
    gluLookAt(Seta, 3.5 + Delta, 3.5, FocusX, FocusY, FocusZ, 0.0, 1.0, 0.0); // 시점변환함수(카메라위치, 초점, 카메라 기울임)

    DrawGround(); // 바닥그리기(시점좌표계를 기준으로)

    glColor3f(1.0, 1.0, 0.0); // 노란색으로
    glutWireTeapot(1.0); // 주전자 그리기

    glFlush();
}
void MySpecial(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP: // 위쪽 키를 누르면
        Delta = Delta + 0.1; // 카메라의 Y축 좌표가 0.1씩 증가
        break;
    case GLUT_KEY_DOWN: // 다운키를 누르면
        Delta = Delta - 0.1; // 카메라의 Y축 좌표가 0.1씩 감소
        break;
    case GLUT_KEY_LEFT: // 왼쪽키 누르면
        Seta = Seta - 0.1; // 카메라의 X축 좌표가 0.1씩 감소
        break;
    case GLUT_KEY_RIGHT: // 오른쪽 누르면
        Seta = Seta + 0.1; // 카메라의 X축 좌표가 0.1씩 증가
        break;

    default:
        break;
    }

    glutPostRedisplay();
}
void MyKeyboard(unsigned char key, int x, int y) { // 키보드 콜백 함수
    switch (key) {
    case 'a': // A,a를 누르면
    case 'A':
        FocusX = FocusX + 0.1; // 초점의 X축 좌표를 0.1씩 증가
        break;
    case 'f': // F,f를 누르면
    case 'F':
        FocusX = FocusX - 0.1; // 초점의 X축 좌표를 0.1씩 감소
        break;
    case 'r': // R,r을 누르면
    case 'R':
        FocusY = FocusY + 0.1; // 초점의 Y축 좌표를 0.1씩 증가
        break;
    case 'v': // V,v 을 누르면
    case 'V':
        FocusY = FocusY - 0.1; // 초점의 Y축 좌표를 0.1씩 감소
        break;
    case 'z': // Z,z 를 누르면
    case 'Z':
        FocusZ = FocusZ + 0.1; // 초점의 Z축 좌표를 0.1씩 증가
        break;
    case 't': // T,t 를 누르면
    case 'T':
        FocusZ = FocusZ - 0.1; // 초점의 Z축 좌표를 0.1씩 감소
        break;
    default:
        break;
    }
    glutPostRedisplay(); // 디스플레이 콜백함수 인위적 호출
}

void MyReshape(int w, int h) { // 윈도우 조정에따른 왜곡을 막아주는 함수
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (GLsizei)w / (GLsizei)h, 0.0, 100); // 원근투영함수
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("VCS (View Coordinate System)");
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(MyDisplay); // 콜백함수 등록
    glutReshapeFunc(MyReshape);
    glutSpecialFunc(MySpecial);
    glutKeyboardFunc(MyKeyboard);

    glutMainLoop();
    return 0;
}