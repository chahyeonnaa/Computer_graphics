/***********************************************************************/
/*                 HW#5-1 : gluLookAt()�� �ǽð� ����                  */
/*  �ۼ��� : ������                           ��¥ : 2021�� 10�� 29��  */
/*                                                                     */
/* ���� ���� : �ڵ� 6-8 ����                                           */
/*                                                                     */
/* ��� : ����Ű ���ۿ����� Camera X,Y���� ��ǥ�� 0.1�� ���� Ȥ�� ���� */
/*        A(a),F(f),R(r),V(v),Z(z),T(t)�� ���������� ������ X,Y��ǥ��  */
/*        0.1�� ���� Ȥ�� ����                                         */
/***********************************************************************/
#include <GL/glut.h>
float Delta = 0; // ī�޶� ��ġ ��������
float Seta = 0; // ī�޶� ��ġ ��������
float FocusX = 0; // ���� ��ġ ��������
float FocusY = 0; // ���� ��ġ ��������
float FocusZ = 0; // ���� ��ġ ��������
void DrawGround() // �ٴڱ׸���
{ 
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON); // �簢�� �׸���(�عٴ�)
    glVertex3f(-2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, -2.0);
    glVertex3f(-2.0, -0.71, -2.0);
    glEnd();

    glColor3f(0.3, 0.3, 0.3);

    glBegin(GL_LINES); // �عٴڿ� �ٱ߱�
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

    // ������� �������
    // Ű�� �����Կ����� 0.1��ŭ�� ī�޶���ġ, ������ ������
    gluLookAt(Seta, 3.5 + Delta, 3.5, FocusX, FocusY, FocusZ, 0.0, 1.0, 0.0); // ������ȯ�Լ�(ī�޶���ġ, ����, ī�޶� �����)

    DrawGround(); // �ٴڱ׸���(������ǥ�踦 ��������)

    glColor3f(1.0, 1.0, 0.0); // ���������
    glutWireTeapot(1.0); // ������ �׸���

    glFlush();
}
void MySpecial(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP: // ���� Ű�� ������
        Delta = Delta + 0.1; // ī�޶��� Y�� ��ǥ�� 0.1�� ����
        break;
    case GLUT_KEY_DOWN: // �ٿ�Ű�� ������
        Delta = Delta - 0.1; // ī�޶��� Y�� ��ǥ�� 0.1�� ����
        break;
    case GLUT_KEY_LEFT: // ����Ű ������
        Seta = Seta - 0.1; // ī�޶��� X�� ��ǥ�� 0.1�� ����
        break;
    case GLUT_KEY_RIGHT: // ������ ������
        Seta = Seta + 0.1; // ī�޶��� X�� ��ǥ�� 0.1�� ����
        break;

    default:
        break;
    }

    glutPostRedisplay();
}
void MyKeyboard(unsigned char key, int x, int y) { // Ű���� �ݹ� �Լ�
    switch (key) {
    case 'a': // A,a�� ������
    case 'A':
        FocusX = FocusX + 0.1; // ������ X�� ��ǥ�� 0.1�� ����
        break;
    case 'f': // F,f�� ������
    case 'F':
        FocusX = FocusX - 0.1; // ������ X�� ��ǥ�� 0.1�� ����
        break;
    case 'r': // R,r�� ������
    case 'R':
        FocusY = FocusY + 0.1; // ������ Y�� ��ǥ�� 0.1�� ����
        break;
    case 'v': // V,v �� ������
    case 'V':
        FocusY = FocusY - 0.1; // ������ Y�� ��ǥ�� 0.1�� ����
        break;
    case 'z': // Z,z �� ������
    case 'Z':
        FocusZ = FocusZ + 0.1; // ������ Z�� ��ǥ�� 0.1�� ����
        break;
    case 't': // T,t �� ������
    case 'T':
        FocusZ = FocusZ - 0.1; // ������ Z�� ��ǥ�� 0.1�� ����
        break;
    default:
        break;
    }
    glutPostRedisplay(); // ���÷��� �ݹ��Լ� ������ ȣ��
}

void MyReshape(int w, int h) { // ������ ���������� �ְ��� �����ִ� �Լ�
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (GLsizei)w / (GLsizei)h, 0.0, 100); // ���������Լ�
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("VCS (View Coordinate System)");
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(MyDisplay); // �ݹ��Լ� ���
    glutReshapeFunc(MyReshape);
    glutSpecialFunc(MySpecial);
    glutKeyboardFunc(MyKeyboard);

    glutMainLoop();
    return 0;
}