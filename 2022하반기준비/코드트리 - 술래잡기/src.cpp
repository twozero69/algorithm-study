#include <iostream>
#include <stack>
#include <math.h>
using namespace std;

#define RIGHT 0
#define SOUTH 1
#define LEFT 2
#define NORTH 3

typedef struct runner
{
    int row;
    int col;
    int dir;
}Runner;

typedef struct move
{
    int step = 1;
    int moveCount = 0;
    int rotateCount = 0;
    bool reverse = false;
    stack<int> revDirs;
}Move;

typedef struct tracer
{
    int row;
    int col;
    int dir = NORTH;
    Move move;
}Tracer;

typedef struct shell
{
    bool tree = false;
    stack<Runner> runners;
    stack<Runner> copy;
}Shell;

int N, M, H, K;
Shell map[99][99];
int result = 0;
Tracer tracer;
int turn;
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };

void moveForward();
void moveReverse();

void init()
{
    cin >> N >> M >> H >> K;

    for (int i = 0; i < M; i++)
    {
        Runner term;
        cin >> term.row >> term.col >> term.dir;
        term.row--;
        term.col--;
        term.dir--;
        map[term.row][term.col].runners.push(term);
    }

    for (int i = 0; i < H; i++)
    {
        int row, col;
        cin >> row >> col;
        map[row - 1][col - 1].tree = true;
    }

    tracer.row = N / 2;
    tracer.col = N / 2;
}

void moveRunner()
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            map[row][col].copy = map[row][col].runners;
            while (!map[row][col].runners.empty())
                map[row][col].runners.pop();
        }
    }

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            stack<Runner>& copy = map[row][col].copy;
            while (!copy.empty())
            {
                Runner runner = copy.top();
                copy.pop();

                if (abs(runner.row - tracer.row) + abs(runner.col - tracer.col) > 3)
                {
                    map[row][col].runners.push(runner);
                    continue;
                }

                int nextRow = runner.row + dy[runner.dir];
                int nextCol = runner.col + dx[runner.dir];

                if (nextRow < 0 || nextRow >= N || nextCol < 0 || nextCol >= N)
                {
                    runner.dir = (runner.dir + 2) % 4;
                    nextRow = runner.row + dy[runner.dir];
                    nextCol = runner.col + dx[runner.dir];
                }

                if (nextRow == tracer.row && nextCol == tracer.col)
                {
                    map[row][col].runners.push(runner);
                    continue;
                }

                runner.row = nextRow;
                runner.col = nextCol;
                map[runner.row][runner.col].runners.push(runner);
            }
        }
    }
}

void moveReverse()
{
    tracer.row += dy[tracer.dir];
    tracer.col += dx[tracer.dir];

    if (tracer.row == N / 2 && tracer.col == N / 2)
    {
        tracer.move.step = 1;
        tracer.move.moveCount = 0;
        tracer.move.rotateCount = 0;
        tracer.move.reverse = false;
        tracer.dir = NORTH;
        return;
    }

    tracer.dir = tracer.move.revDirs.top();
    tracer.move.revDirs.pop();
}

void moveForward()
{
    int nextRow = tracer.row + dy[tracer.dir];
    int nextCol = tracer.col + dx[tracer.dir];

    tracer.row = nextRow;
    tracer.col = nextCol;
    tracer.move.revDirs.push((tracer.dir + 2) % 4);
    if (nextRow == 0 && nextCol == 0)
    {
        tracer.move.reverse = true;
        tracer.dir = tracer.move.revDirs.top();
        tracer.move.revDirs.pop();
        return;
    }

    tracer.move.moveCount++;
    if (tracer.move.moveCount == tracer.move.step)
    {
        tracer.dir = (tracer.dir + 1) % 4;
        tracer.move.moveCount = 0;
        tracer.move.rotateCount++;
        if (tracer.move.rotateCount == 2)
        {
            tracer.move.rotateCount = 0;
            tracer.move.step++;
        }
    }
}

void moveTracer()
{
    if (tracer.move.reverse)
        moveReverse();
    else
        moveForward();
}

void catchRunner()
{
    for (int i = 0; i < 3; i++)
    {
        int checkRow = tracer.row + dy[tracer.dir] * i;
        int checkCol = tracer.col + dx[tracer.dir] * i;
        if (checkRow < 0 || checkRow >= N || checkCol < 0 || checkCol >= N)
            break;
        stack<Runner>& runners = map[checkRow][checkCol].runners;
        if (map[checkRow][checkCol].tree || runners.empty())
            continue;
        result += turn * runners.size();
        while (!runners.empty())
            runners.pop();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    for (turn = 1; turn <= K; turn++)
    {
        moveRunner();
        moveTracer();
        catchRunner();
    }
    cout << result;

    return 0;
}