/*  Developed a captivating 2D space rocket game using GLUT (OpenGL Utility Toolkit) and OpenGL. Implemented intuitive controls, allowing players to navigate the rocket with their mouse. Incorporated laser beam mechanics with color-changing functionality. Created 25 random asteroids that players had to hit with matching color laser beams to earn points. Implemented a scoring system and a 20 second timer. Provided a restart option for replayability. Demonstrated proficiency in graphics programming, game mechanics, and user interface design. */

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <ctime>
#include <cmath>
#include <cstdlib>
#include <stdio.h>

#define windowWidth 800
#define windowHeight 600

int finalScore;
int score = 0;  // Game score
int counter = 20;   // Timer counter
int laserFlag = 0;  // Laser color flag
int asteroidIndex = 0;
int phyWidth = 700;
int phyHeight = 700;
int logWidth = 100;
int logHeight = 100;
int centerX = logWidth / 2;
int centerY = logHeight / 2;
int mouseX = centerX, mouseY = centerY; // Mouse coordinates
const int numAsteroids = 25;
bool scoreFlag = true;

class LaserBeam {
public:
    GLfloat startX;
    GLfloat startY;
    GLfloat endX;
    GLfloat endY;
    
public:
    GLfloat x;
    GLfloat y;
    GLfloat width;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    
    LaserBeam(GLfloat startX, GLfloat startY, GLfloat endX, GLfloat endY, GLfloat width, GLfloat red, GLfloat green, GLfloat blue, GLfloat x,GLfloat y) {
        this->startX = startX;
        this->startY = startY;
        this->endX = endX;
        this->endY = endY;
        this->width = width;
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->x = x;
        this->y = y;
    }
    
    void draw() {
        glPushMatrix();
        glLineWidth(width);
        glColor3f(red, green, blue);
        glBegin(GL_LINES);
        glVertex2f((startX + x) / 10.0, (startY-y) / 10.0);
        glVertex2f((endX + x) / 10.0, (endY-y) / 10.0);
        glEnd();
        glPopMatrix();
    }
    
    void setColor(GLfloat red, GLfloat green, GLfloat blue) {
        this->red = red;
        this->green = green;
        this->blue = blue;
        glutPostRedisplay();
    }
    void updatePosition(float newX,float newY) {
        x = newX * 10;
        y = newY * 10;
    }
};

class spaceRocket {
public:
    GLfloat x;
    GLfloat y;
    
public:
    spaceRocket(GLfloat x, GLfloat y) {
        this->x = x;
        this->y = y;
    }
    
    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
        glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
    }
    void drawRectangle(float x1, float y1, float x2, float y2) {
        glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
        glEnd();
    }
    
    void draw() {
        // Set the color for the bottom triangle of the rocket
        glColor3f(251.0 / 255.0, 141.0 / 255.0, 0.0);
        drawTriangle((-0.5 + x) / 10.0, (-0.5 -y) / 10.0, (0.5 + x) / 10.0, (-0.5-y) / 10.0, 0.0 + x / 10.0, (0.05-y) / 10.0);
        
        // Set the color for the body of the rocket (rectangle)
        glColor3f(80.0 / 255.0, 189.0 / 255.0, 250.0 / 255.0);
        drawRectangle((-0.2 + x) / 10.0, (-0.5-y) / 10.0, (0.2 + x) / 10.0, (0.5-y) / 10.0);
        
        // Set the color for the top triangle of the rocket
        glColor3f(251.0 / 255.0, 141.0 / 255.0, 0.0);
        drawTriangle((-0.2 + x) / 10.0, (0.5-y) / 10.0, (0.2 + x) / 10.0, (0.5-y) / 10.0, 0.0 + x / 10.0, (0.8-y) / 10.0);
    }
    
    void updatePosition(float newX,float newY) {
        x = newX * 10;
        y = newY * 10;
    }
};

class Asteroid {
public:
    int x;
    GLfloat y;
    GLfloat radius;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    bool visible;
    
    Asteroid(GLfloat radius, GLfloat red, GLfloat green, GLfloat blue) {
        this->x = generateRandomX();
        this->y = logHeight / 10.0 - radius;
        this->radius = radius;
        visible = true;
        generateRandomRGB();
    }
    
    Asteroid() {
        x = 0.0f;
        y = 0.0f;
        radius = 0.0f;
        red = 0.0f;
        green = 0.0f;
        blue = 0.0f;
    }
    
    // Function to generate a random x-coordinate for the asteroid within a specified range
    GLfloat generateRandomX() {
        GLfloat x = static_cast<GLfloat>(rand() % 20) - 10.0;
        return x;
    }
    
    void minY(){
        y-=0.1;
    }
    
    void generateRandomRGB() {
        // Generate a random number between 0 and 1
        GLfloat x = static_cast<GLfloat>(rand()%(3));
        if(x==0.0)
        {
            red=1.0;
            green=0.0;
            blue=0.0;
        }
        else if(x==1.0)
        {
            red=0.0;
            green=1.0;
            blue=0.0;
        }
        else{
            red=0.0;
            green=0.0;
            blue=1.0;
        }
    }
    
    void circle() {
        glColor3f(red, green, blue);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float theta = i * 3.14159 / 180.0;
            float px = radius * cos(theta);
            float py = radius * sin(theta);
            glVertex2f((x + px)/10.0, (y + py)/10.0);
        }
        glEnd();
    }
    
    void draw() {
        circle();
    }
};

LaserBeam laser(0.0f, 0.0f, 0.0f, 50.0f, 40.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
spaceRocket rocket(0.0f,0.0f);
Asteroid asteroids[numAsteroids];

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        if(laserFlag==0){
            laser.setColor(0.0f,1.0f,0.0f);
            laserFlag++;
        }
        
        else if(laserFlag==1){
            laser.setColor(0.0f,0.0f,1.0f);
            laserFlag++;
        }
        
        else{
            laser.setColor(1.0f,0.0f,0.0f);
            laserFlag=0;
        }
    }
}

void timer(int value)
{
    if (counter > 0)
    {
        counter--;
        glutTimerFunc(1000, timer, 0);
    }
    
    if(counter==0&&scoreFlag){
        finalScore=score;
        scoreFlag=false;
    }
    
    glutPostRedisplay();
}

void reset() {
    score = 0;
    counter = 20;
    scoreFlag = true;
    asteroidIndex = 0;

    for (int i = 0; i < asteroidIndex; i++) {
        asteroids[i] = Asteroid(0.5f, 1.0f, 0.0f, 0.0f);
    }
    
    glutTimerFunc(1000, timer, 0);
}

void specialKeyboard(int key, int x, int y){
    if(key==GLUT_KEY_F1){
        reset();
    }
}

void mouse(int x, int y) {
    mouseX = x;
    mouseY = y;

    float newX = -1.0f + (2.0f * mouseX) / windowWidth;
    float newY = -1.0f + (2.0f * mouseY) / windowWidth;

    rocket.updatePosition(newX, newY);
    laser.updatePosition(newX, newY);

    glutPostRedisplay();
}

void moveAsteroids(int value){
    for(int i=0;i<asteroidIndex;i++){
        asteroids[i].minY();
    }
    glutTimerFunc(50, moveAsteroids, 0);
    glutPostRedisplay();
}

void checkCollision(Asteroid& asteroid,LaserBeam& laser) {
    
    if (asteroid.visible&&laser.y > asteroid.y &&  laser.x<(asteroid.x+asteroid.radius)&&laser.x>(asteroid.x-asteroid.radius) && laser.blue==asteroid.blue && laser.red==asteroid.red && laser.green==asteroid.green) {
        asteroid.visible=false;
        score++;
    }
}

void drawStars() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(1.0f);
    glBegin(GL_POINTS);

    for (int i = 0; i < 200; i++) {
        float x = static_cast<float>(rand() % windowWidth) / windowWidth * 2.0f - 1.0f;
        float y = static_cast<float>(rand() % windowHeight) / windowHeight * 2.0f - 1.0f;
        glVertex2f(x, y);
    }

    glEnd();
}

void drawText() {
    char text[20];

    if (counter > 0) {
        snprintf(text, sizeof(text), "Time Left: %d", counter);
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(-0.9, 0.9);

        for (int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    else {
        snprintf(text, sizeof(text), "Final Score: %d", finalScore);
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(-0.9, 0.9);

        for (int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

        char gameOverText[] = "GAME OVER!";
        glColor3f(1.0, 0.0, 0.0);
        glRasterPos2f(-0.13, 0.0);

        for (int i = 0; gameOverText[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gameOverText[i]);
    }
}

void drawScore(){
    if(scoreFlag){
        char text[20];
        
        snprintf(text, sizeof(text), "Score: %d", score);
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(0.7, 0.9);
        
        for (int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        
        glutSwapBuffers();
    }
}

void asteroidTimer(int value) {
    if (asteroidIndex < numAsteroids) {
        asteroids[asteroidIndex] = Asteroid(0.5f, 1.0f, 0.0f, 0.0f);
        asteroidIndex++;
    }
    glutTimerFunc(700, asteroidTimer, 0);
}

// Display callback function
void display() {
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    drawStars();
    drawText();
    drawScore();
    laser.draw();
    rocket.draw();
    
    for (int i=0;i<asteroidIndex;i++){
        checkCollision(asteroids[i], laser);
        
        if (asteroids[i].visible) {
            asteroids[i].draw();
        }
    }
    glFlush();
}

int main(int argc, char** argv) {
    // Initialize GLUT and create the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Space Rocket");
    
    // Set the display and input functions
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutPassiveMotionFunc(mouse);
    
    // Set the timer function
    glutTimerFunc(1000, timer, 0);
    
    // Set the full screen and hide the cursor
    glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE);
    
    // Call additional functions
    asteroidTimer(1);
    moveAsteroids(1);
    
    // Start the main GLUT loop
    glutMainLoop();
    
    return 0;
}
