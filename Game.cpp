#include "Game.h"

using namespace std;

Game::Game(){
  string name;
  Game::GameTitle();
  Game::LoadMaterials();

  cout << "What is the name of your Diver?" << endl;
  getline(cin, name);
  //puts the divers name into name and sets the name
  m_myDiver.SetName(name);

}

void Game::StartGame(){
  int depthWin = 0;
  int choice = 0;
  int stop = 0;
  

  
  //if the depth is less than 1000 it keeps running
  while ((depthWin < MAX_DEPTH) || (stop < MAX_DEPTH)){

    choice = Game::MainMenu();
    
    switch (choice){

    case 1:

      Game::DisplayMaterials();     
     break;
    
    case 2:
      //searchs for materials
      Game::SearchMaterials();
      break;

    case 3:
      //combines 2 materials and adds the depth and then sets it to depthWin
      Game::CombineMaterials();
      depthWin = m_myDiver.CalcDepth(0);
      
      break;

    case 4:
      //shows the score
      Game::CalcScore();
      break;

    case 5: 

      //if the players quits it shows the score and sets stop to 1000
      Game::CalcScore();
      cout << "Thank you for playing, GoodBye" << endl; 
      stop = 1000;
      break;

    }
  }
  if (depthWin > MAX_DEPTH){
    //if the user gets to the max depth, then they win and the results are shown
    
    cout << "Congratulations, you won!" << endl << "Here are the results: " << endl;

    Game::CalcScore();

    cout << "Thank you for playing, Goodbye" << endl;
  }
}
  
void Game::LoadMaterials(){
  ifstream textFile;
  
  string item, type, material1, material2;
  

  int quantity = 0, depth;
  
  //opens file
  textFile.open(PROJ2_DATA);
  
  if (textFile.is_open()){
    for (int i = 0; i < PROJ2_SIZE; i++){

      //puts the name, type , material 1 and 2, quantity, and depth into the
      // materialw array
      getline(textFile, item,',');
      m_myDiver.AddMaterial(item);
      getline(textFile, type,',');
      getline(textFile, material1,',');
      getline(textFile, material2,',');
      textFile>> depth; 
      textFile.ignore(256,'\n');

      m_materials[i] = Material(item, type, material1, material2, quantity, depth);
    }
  }
  // closes file
  textFile.close();
  cout << "50 materials loaded" << endl;
}

int Game::MainMenu(){
  int choice;

  //asks what the user wants to do
  cout << "What would you like to do?" << endl;
  cout << "1. Display your Diver'sMaterials" << endl;
  cout << "2. Search for RawMaterials" << endl;
  cout << "3. Attempt to merge Materials" << endl;
  cout << "4. See Score" << endl;
  cout << "5. Quit" << endl;

  
  cin >> choice;
  
  while ((choice < 1) || (choice > 5)){

    //if its less than one or higher than 5, it reprompts
    cout << "Please try again" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1. Display your Diver'sMaterials" << endl;
    cout << "2. Search for RawMaterials" << endl;
    cout << "3. Attempt to merge Materials" << endl;
    cout << "4. See Score" << endl;
    cout << "5. Quit" << endl;
    
    cin >> choice;
  }
  return choice; //returns their choice
}

void Game::DisplayMaterials(){
  //Displays the name and quantity of the material
  m_myDiver.DisplayMaterials();
}

void Game::SearchMaterials(){
  int rndNum;
  //searches for a item randomly
  const string TYPE = "raw";
  srand(time(NULL));
  const int MAX = 50, MIN = 1;

  //random number from 1 to 50
  rndNum = (rand() % MAX + 1 - MIN) + MIN;
  
  //if the random number isnt a material that is raw then it will pick a different number again
  while (m_materials[rndNum].m_type != TYPE){
    rndNum = (rand() % MAX + 1 - MIN) + MIN;

  }

  cout << "You've obtained " << m_materials[rndNum].m_name << endl;
  //adds the material to the quantity
  m_myDiver.IncrementQuantity(m_materials[rndNum]);
}

void Game::CombineMaterials(){
  int material1 = 0;
  int material2 = 0;
  string num1;

  //asks for 2 materials to combine  
  Game::RequestMaterial(material1);
  Game::RequestMaterial(material2);
  //if the diver doesnt have the item then it wont work
  if ((m_myDiver.CheckMaterial(m_materials[material1]) != -1) && (m_myDiver.CheckMaterial(m_materials[material2]) != -1))
    //searches for the recipe with the 2 materials
    Game::SearchRecipes(m_materials[material1].m_name, m_materials[material2].m_name);
}

void Game::RequestMaterial(int& choice){
  const int LIST = -1;
  //asks what material to merge
  cout << "Which materials would you like to merge?" << endl;
  cout << "To list known materials enter -1" << endl;
  
  cin >> choice;
  
  //if choice is -1 then it prints the list of materials and quantity
  
  while ((choice < 0) || (choice > 50)){
    
    if (choice == LIST){
      m_myDiver.DisplayMaterials();
    }
    
    cout << "Please try again" << endl;
    cout << "Which materials would you like to merge?" << endl;
    cout << "To list known materials enter -1" << endl;
    
    cin >> choice;
  }
  //if user picks something that isnt 0 then it will subtract one
  if (choice != 0)
    choice -= 1;
  else
    choice = -1;
}


int Game::SearchRecipes(string item1, string item2){
  
  Material material1, material2;
  //loop for the item the user is trying to make
  for (int i = 0; i < PROJ2_SIZE; i++){
    // finds the item recipe with the chosen materials

    if ((m_materials[i].m_material1 == item1) || (m_materials[i].m_material1 == item2)) 
      if ((m_materials[i].m_material2 == item1) || (m_materials[i].m_material2 == item2)){

	//loop for the materials
	for (int x = 0; x < PROJ2_SIZE; x++){
	  
	  //finds first material sets it to material 1
	  if (m_materials[x].m_name == item1){
	    material1 = m_materials[x];
	  }
	}

	for (int y = 0; y < PROJ2_SIZE; y++){
	  //finds the second material and sets it to material 2

	  if (m_materials[y].m_name == item2){
	    material2 = m_materials[y];
	  }
	}
	
	//if both material 1 and 2 have quantities higher than 1
	//then it will turn true

	if (m_myDiver.CheckQuantity(material1, material2) == true){

	  //decreases the quantity of material 1 and 2 
	  m_myDiver.DecrementQuantity(material1);
	  m_myDiver.DecrementQuantity(material2);
	  
	  //increments the quantity of the item that they made
	  m_myDiver.IncrementQuantity(m_materials[i]);

	  //adds depth
	  m_myDiver.CalcDepth(m_materials[i].m_depth);
	  
	  cout << material1.m_name << " and " << material2.m_name << " made " << m_materials[i].m_name << endl;
	  //returns the int indec of matching recipe
	  return i;
	  
	}
	else{
	  cout << "You dont have enough " << item1 << " or " << item2 << " to attempt that merge" << endl;
	  
	}
      }
    
  }
  
  cout << item1 << " and " << item2 <<" makes nothing" << endl; 
  return -1;
}

void Game::CalcScore(){
  //prints out the diver name and the depth they are at
  cout << "***The Diver***" << endl;
  cout <<"Ther Great Diver " << m_myDiver.GetName() << endl;
  cout << "The Maximim Depth: " << MAX_DEPTH << endl;
  cout << "Current Depth: " << m_myDiver.CalcDepth(0) << endl;
}
