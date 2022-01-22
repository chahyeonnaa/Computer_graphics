/***********************************************************************/
/*                 HW#3-4 : Menu Callback ����                         */
/*  �ۼ��� : ������                           ��¥ : 2021�� 10�� 1��   */
/*                                                                     */
/* ���� ���� : �˸��� ����� ����ǵ��� �ڵ� 5-6 ����                  */
/*                                                                     */
/* ��� : �ָ޴� : Draw Sphere, Draw Torus, Draw Teapot, Change Color, Exit */
/*       Draw Sphere �Ϻ� �޴� : Small Sphere, Large Sphere            */
/*        Draw Torus �Ϻ� �޴� : Small Torus , Large Torus             */
/*        Draw Teapot �Ϻ� �޴� : Small Teapot , Large Teapot          */
/*        Change Color �Ϻ� �޴� : Red, Green, Blue                    */
/***********************************************************************/
#include <GL/glut.h>

float r = 0.0;
float g = 0.0;
float b = 0.0;// ���� ����(����Ʈ ����)

// �޴��ݹ� �Լ����� ���̵� ������ draw���� �Ҵ��Ͽ� MyDisplay()�� �����Ͽ� �׸��� �׸���.
int draw = 1; // �� �������� �׸��� ���� ����, �Ҵ�Ǵ� ���ڵ�� �������� ������

void MyDisplay() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    switch (draw) {
    case 1: // ū ��
        glColor3f(r, g, b);
        glutWireSphere(0.7, 30, 30);
        break;
    case 2: // ���� ��
        glColor3f(r, g, b);
        glutWireSphere(0.5, 30, 30);
        break;
    case 3: // ���� �䷯��
        glColor3f(r, g, b);
        glutWireTorus(0.1, 0.3, 40, 20);
        break;
    case 4: // ū �䷯��
        glColor3f(r, g, b);
        glutWireTorus(0.2, 0.5, 40, 20);
        break;
    case 5: // ���� ������
        glColor3f(r, g, b);
        glutWireTeapot(0.35);
        break;
    case 6: // ū ������
        glColor3f(r, g, b);
        glutWireTeapot(0.55);
        break;
    default:
        break;
    }

    glFlush();
}

void MySphereMenu(int entryID) { // �� �׸���
    if (entryID == 1)           draw = 1; // ū��
    else if (entryID == 2)      draw = 2; // ������ �׸���

    glutPostRedisplay();
}

void MyTorusMenu(int entryID) { // �䷯�� �׸���
    if (entryID == 1)           draw = 3; // ������
    else if (entryID == 2)      draw = 4; // ū��

    glutPostRedisplay();
}

void MyTeapotMenu(int entryID) { // ������ �׸���
    if (entryID == 1)           draw = 5; // ������
    else if (entryID == 2)      draw = 6; // ū��

    glutPostRedisplay();
}

void MyColorMenu(int entryID) {
    if (entryID == 1) // �޴������� �Ҵ�� ��ȣ�� 1�� �׸��� Ŭ���ϸ�
        r = 1.0, g = 0.0, b = 0.0; // ����
    else if (entryID == 2) // �޴������� �Ҵ�� ��ȣ�� 1�� �׸��� Ŭ���ϸ�
        r = 0.0, g = 1.0, b = 0.0; // �׸�
    else if (entryID == 3) // �޴������� �Ҵ�� ��ȣ�� 1�� �׸��� Ŭ���ϸ�
        r = 0.0, g = 0.0, b = 1.0; // ���
    glutPostRedisplay(); // ���÷��� �ݹ��Լ� ���������� ȣ���ϱ�
}

void MyMainMenu(int entryID) { // �ָ޴�
    if (entryID == 3)            exit(0); // �ָ޴����� ���̵� 3�� �ش��ϴ°� ������, ���α׷� ����

    glutPostRedisplay(); 
}

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    GLint Mysphere = glutCreateMenu(MySphereMenu); // ����޴� ����
    glutAddMenuEntry("Large Sphere", 1); // �޴��׸� ÷��
    glutAddMenuEntry("Small Sphere", 2); // ���ڴ� �׸��� ���õɶ� �޴��ݹ� �Լ����� ���޵Ǵ� ������

    GLint Mytorus = glutCreateMenu(MyTorusMenu); // ����޴� ����
    glutAddMenuEntry("Small Torus", 1); // �޴��׸� ÷��
    glutAddMenuEntry("Large Torus", 2);

    GLint Myteapot = glutCreateMenu(MyTeapotMenu); // ����޴� ����
    glutAddMenuEntry("Small Teapot", 1); // �޴��׸� ÷��
    glutAddMenuEntry("Large Teapot", 2);

    GLint Mycolor = glutCreateMenu(MyColorMenu); // ����޴� ����
    glutAddMenuEntry("Red", 1); // �޴��׸� ÷��
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu); // �ָ޴� ����(���̵� �� ����)
    glutAddSubMenu("Draw Sphere", Mysphere); // ����޴��׸� �߰�_ �޴����� ������ �ݹ��Լ� ����ؾ���
    glutAddSubMenu("Draw Torus", Mytorus);
    glutAddSubMenu("Draw Teapot", Myteapot);
    glutAddSubMenu("Change Color", Mycolor);
    glutAddMenuEntry("Exit", 3); // ����޴��� �ƴ� �޴��׸� �߰�(�ָ޴����� 3�� �Ҵ�)
    glutAttachMenu(GLUT_RIGHT_BUTTON); // ������ ���콺 ��ư�� �޴� �Ҵ�(�������� ������ �޴��� �˾�)

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500, 500); // �����������
    glutInitWindowPosition(0, 0); // ������ ��ġ
    glutCreateWindow("Menu Callback");
    MyInit();

    glutDisplayFunc(MyDisplay); // ���÷��� �ݹ��Լ� ���

    glutMainLoop();
    return 0;
}