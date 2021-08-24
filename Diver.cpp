#include "Diver.h"

//Constructor
Diver::Diver(){
  m_myName = "aaron";
  m_numMaterials = PROJ2_SIZE;
  
}

Diver::Diver(string name) {
  m_myName = name;
  m_numMaterials = PROJ2_SIZE;
}

string Diver::GetName(){
  return m_myName;
}

void Diver::SetName(string name){
  m_myName = name;

}

void Diver::DisplayMaterials(){
  //displays the material name and quantity
  for (int i = 0; i < PROJ2_SIZE; i++){
    cout << i+1 << ". " <<  m_myMaterials[i].m_name << " " << m_myMaterials[i].m_quantity << endl;
  }
}

bool Diver::CheckQuantity(Material item1, Material item2){
  Material material1, material2;

  //if both items are the same
  if (item1.m_name == item2.m_name){
    
    //they are going to loop to find one of the material
    for (int k = 0; k < PROJ2_SIZE; k++){
      if (m_myMaterials[k].m_name == item1.m_name)
	material1 = m_myMaterials[k];
    }
    
    //if the quantity for the material is greater than 1 then return true
    if (material1.m_quantity > 1){
      return true;
    }
  }
  
  //if both of the items are different
  else{
      
    //they are going to loop the material list to find them and append it to material 1 and 2
    for (int i = 0; i < PROJ2_SIZE; i++){
      if (m_myMaterials[i].m_name == item1.m_name)
	material1 = m_myMaterials[i];
    }
    
    for (int j = 0; j < PROJ2_SIZE; j++){
      if (m_myMaterials[j].m_name == item2.m_name)
	material2 = m_myMaterials[j];
    }
    
    //then checks material 1 and 2, if both of their quantity is greater than 0 then return true
    if ((material1.m_quantity > 0) && (material2.m_quantity > 0)){
      return true;
    }
  }
  //else returns false
  return false;
  
}


void Diver::IncrementQuantity(Material item){

  //adds 1 quantity to the material  
  for (int i = 0; i < PROJ2_SIZE; i++)

    if (m_myMaterials[i].m_name == item.m_name){
    
      m_myMaterials[i].m_quantity += 1;
    }
}

void Diver::DecrementQuantity(Material item){
  //deceases 1 quantity to the material 
  for (int i = 0; i < PROJ2_SIZE; i++)

    if (m_myMaterials[i].m_name == item.m_name){

      m_myMaterials[i].m_quantity -= 1;
    }


}

void Diver::AddMaterial(string item){
  string type = "material", material1 = "NA", material2 = "NA", name;
  int depth = 0, quantity = 0;
  name = item;

  //loops the diver list
  for (int i = 0; i < PROJ2_SIZE; i++)

    //if the index of the m_myMaterial[i].m_name isnt type then it will appends 
    if (m_myMaterials[i].m_type != type){ 

      //appends the name of the material and quantity but the rest are 0 or NA
    m_myMaterials[i] = Material(name, type, material1, material2, quantity, depth);

    //once it appends, i turns to PROJ2_SIZE so it wont append multiple times
    i = PROJ2_SIZE;   
    }
}

int Diver::CalcDepth(int depth){
  //uses m_myMaterial[1].m_depth as a default to save the depth of the user
  //adds the depth with m_myMaterial[1].m_depth and return it 
  return m_myMaterials[1].m_depth += depth;
  
}

int Diver::CheckMaterial(Material item){
  //loops and find the material
  for (int i = 0; i < PROJ2_SIZE; i++){
    //if they are both same it returns the index
    if (m_myMaterials[i].m_name == item.m_name)
      return i;
	}
  //else returns -1
  return -1;
}
