#include <iostream>
#include <deque>

#include <raylib.h>
#include <raymath.h>

Color back = {173, 204,96, 255};
Color front = {43, 51, 24, 255};

int cellSize = 25;
int cellCount = 25;

int offset = 75;

double delta = 0;

bool running = true;

class Food{
public:
  Vector2 position;
  Texture2D texture;

  Food(){
    position = genRandomPos((std::deque<Vector2>){});
    Image image = LoadImage("resourses/images/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
  }

  ~Food(){
    UnloadTexture(texture);
  }

  void Draw(){
    DrawTexture(texture, position.x, position.y, WHITE);
  }

  Vector2 genRandomPos(std::deque<Vector2> snakeBody){
    bool validPosition = false;
    float x;
    float y;
    if(snakeBody.size() == 0){
      return Vector2{
        GetRandomValue(0, cellCount-1) * cellSize,
        GetRandomValue(0, cellCount-1) * cellSize
      };
    }
    while(!validPosition){
      x = GetRandomValue(0, cellCount-1) * cellSize;
      y = GetRandomValue(0, cellCount-1) * cellSize;

      for(int i = 0; i<snakeBody.size(); i+=1){
        if(Vector2Equals(snakeBody[i], Vector2{x,y})){continue;}

        if(i == snakeBody.size()-1){
          validPosition = true;
        }
      }
    }
    return Vector2{x,y};
  }

};

class Snake{
public:
  std::deque<Vector2> body = {Vector2{6*cellSize,9*cellSize}, Vector2{5*cellSize,9*cellSize}, Vector2{4*cellSize,9*cellSize}};

  Vector2 direction = {1, 0};

  bool addSecgment= false;

  void Draw(){
    for(unsigned int i = 0; i<body.size(); i+=1){
      float x = body[i].x;
      float y = body[i].y;
      Rectangle rect_seg = Rectangle{x, y, (float)cellSize, (float)cellSize};
      DrawRectangleRounded(rect_seg, 0.5, 6, front);
    }
  }

  void Update(Food &food){
    // eventKeyPressed();
    CheckCollisionWithEdge(food);
    CollisionWithTail(food);
    body.push_front(Vector2Add(body[0],Vector2{direction.x*cellSize, direction.y*cellSize}));
    if(addSecgment){
      addSecgment = false;
    }else{
      body.pop_back();
    }
  }

  void CheckCollisionWithEdge(Food &food){
    if(body[0].x >= cellSize*cellCount || body[0].y >= cellSize*cellCount ||
       body[0].x <0 || body[0].y < 0){
      GameOver(food);
    }

  }

  void CollisionWithTail(Food &food){
    std::deque<Vector2> headless = body;
    headless.pop_front();

    if(ElementInDeque(body[0], headless)){
      GameOver(food);
    }
  }

  bool ElementInDeque(Vector2 element, std::deque<Vector2> deque){
    for (unsigned int i = 0; i < deque.size(); i++){
      if (Vector2Equals(deque[i], element)){
        return true;
      }
    }
    return false;
  }

  void eventKeyPressed(){
    if(IsKeyPressed(KEY_UP) && direction.y != 1){
      direction = {0, -1};
      running = true;
    }else if (IsKeyPressed(KEY_DOWN) && direction.y != -1){
      direction = {0, 1};
      running = true;
    }else if (IsKeyPressed(KEY_LEFT) && direction.x != 1){
      direction = {-1, 0};
      running = true;
    }else if (IsKeyPressed(KEY_RIGHT) && direction.x != -11){
      direction = {1, 0};
      running = true;
    }
  }

  void GameOver(Food &food){
    Reset();
    food.genRandomPos(body);
    running = false;
  }

  void Reset(){
    body={Vector2{6*cellSize,9*cellSize}, Vector2{5*cellSize,9*cellSize}, Vector2{4*cellSize,9*cellSize}};
    direction = {1,0};
  }

};

void CheckFoodCollistion(Food& food, Snake& snake){
  if(Vector2Equals(snake.body[0], food.position)){
    std::cout<<"Food eaten"<<std::endl;
    food.position = food.genRandomPos(snake.body);
    snake.addSecgment = true;
  }
}

bool eventTriggered(double interval){
  double currentTime = GetTime();
  if(currentTime - delta >= interval){
    delta = currentTime;
    return true;
  }
  return false;
}

int main(int argno, char** args){

  /*
    InitAudioDevice();
    Sound eatSound = LoadSound(/path to sound);
    Sound eatSound = LoadSound(/path to sound);
   */

  InitWindow(cellSize*cellCount, (cellSize*cellCount) + cellSize, "Snake");
  int w = GetScreenWidth();
  int h = GetScreenHeight();

  std::cout<<"Width: "<<w<<", Height: "<<h<<std::endl;
  SetTargetFPS(60);

  Food food = Food();
  Snake snake = Snake();

  while (WindowShouldClose() == false){
    BeginDrawing();
    ClearBackground(back);

    if(eventTriggered(0.2) && running){
      snake.Update(food);
      CheckFoodCollistion(food, snake);
    }

    /*
      PlaySound(sound);
     */

    snake.eventKeyPressed();
    food.Draw();
    snake.Draw();

    EndDrawing();
  }

  /*
    UnloadSound(Sound sound);]
    CloseAudoDevice();
   */

  CloseWindow();
  return 0;

}
