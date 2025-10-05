#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define NUM_FACELETS 54
#define EPSILON 1e-6

typedef struct {
    int x, y, z;
    char color;
} Facelet;

Facelet cube[NUM_FACELETS];
Facelet original[NUM_FACELETS];

int equals(int x1, int y1, int z1, int x2, int y2, int z2) {
    return (x1 == x2 && y1 == y2 && z1 == z2);
}

void rotate90(Facelet *f, char axis) {
    int x = f->x, y = f->y, z = f->z;
    if (axis == 'x') {
        f->y = -z;
        f->z = y;
    } else if (axis == 'y') {
        f->x = z;
        f->z = -x;
    } else if (axis == 'z') {
        f->x = -y;
        f->y = x;
    }
}

void rotate(Facelet *f, char axis, int angle) {
    int times = (angle % 360) / 90;
    for (int i = 0; i < times; ++i) {
        rotate90(f, axis);
    }
}

void apply_rotation(int axis, int pos, int angle) {
    char axis_char = axis == 0 ? 'x' : (axis == 1 ? 'y' : 'z');
    for (int i = 0; i < NUM_FACELETS; i++) {
        int coord = axis == 0 ? cube[i].x : (axis == 1 ? cube[i].y : cube[i].z);
        if (coord == pos) {
            rotate(&cube[i], axis_char, angle);
        }
    }
}

int is_solved() {
    for (int i = 0; i < NUM_FACELETS; i++) {
        int found = 0;
        for (int j = 0; j < NUM_FACELETS; j++) {
            if (equals(cube[i].x, cube[i].y, cube[i].z,
                       original[j].x, original[j].y, original[j].z)) {
                if (cube[i].color != original[j].color)
                    return 0;
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

void input_cube() {
    printf("Enter each facelet as: x y z color (example: -2 2 3 G)\n");
    for (int i = 0; i < NUM_FACELETS; i++) {
        scanf("%d %d %d %c", &cube[i].x, &cube[i].y, &cube[i].z, &cube[i].color);
        original[i] = cube[i];  // Save for solved comparison
    }
}

int rand_choice(int choices[], int len) {
    return choices[rand() % len];
}

int main() {
    srand(time(NULL));
    input_cube();

    int positions[] = {-2, 0, 2};
    int angles[] = {90, 180, 270};

    int moves = 0;
    while (1) {
        for (int i = 0; i < 20; i++) {
            int axis = rand() % 3;
            int pos = rand_choice(positions, 3);
            int angle = rand_choice(angles, 3);

            apply_rotation(axis, pos, angle);
            moves++;
            printf("Move %d: Rotated axis %c=%d by %d degrees\n", moves,
                   axis == 0 ? 'x' : axis == 1 ? 'y' : 'z', pos, angle);
        }

        if (is_solved()) {
            printf("\nCube solved in %d moves!\n", moves);
            break;
        }
    }

    return 0;
}
