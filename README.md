# MODERN_CPP_ENGINE

Petit moteur C++20 autonome avec rendu ASCII, ECS, gestion des entrées et pools
mémoire. Aucune bibliothèque externe n'est nécessaire.

## Compiler et tester

Prérequis : CMake 3.15 ou supérieur et un compilateur compatible C++20.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j2
ctest --test-dir build --output-on-failure
```

La bibliothèque `ModernCppEngine` et l'exécutable `ModernCppEngineApp` sont
construits ensemble. Utiliser `-DBUILD_TESTING=OFF` pour désactiver les tests.

## Lancer la démo

```sh
./build/ModernCppEngineApp
./build/ModernCppEngineApp --interactive
```

Le premier mode affiche une scène et termine. Le mode interactif déplace `@`
dans une grille de 20 × 8 caractères : `z`/`w` pour monter, `s` pour descendre,
`q`/`a` pour aller à gauche, `d` pour aller à droite et `x` pour quitter.
Valider chaque commande avec Entrée. La fin du flux d'entrée quitte également.

## Modules

- **ECS** : `World` crée et recycle les entités. Une génération distingue les
  anciennes références des nouvelles entités utilisant le même identifiant.
  Détruire une entité supprime tous ses composants. `SparseSet` stocke les
  composants de manière dense et `World::forEach<T>` les parcourt.
- **Rendu** : `Renderer` expose un tampon texte, ignore les pixels hors limites
  et refuse les dimensions non positives. `RenderSystem` affiche les entités
  possédant `Position` et `Sprite` et efface la scène à chaque mise à jour.
- **Entrées** : `InputManager` reçoit des événements clavier/souris sans
  dépendance à une fenêtre. Appeler `update()` au début d'une frame, puis
  transmettre les événements. `isKeyPressed` indique une touche maintenue ;
  `wasKeyPressed` et `wasKeyReleased` indiquent les transitions de la frame.
  `InputComponent` conserve des actions nommées par entité.
- **Mémoire** : `MemoryPool` fournit des blocs alignés de capacité fixe ;
  `allocate()` renvoie `nullptr` quand le pool est plein. Le troisième argument
  facultatif précise l'alignement. Une libération étrangère ou répétée lève
  `std::invalid_argument`. `ObjectPool<T>` construit les objets, récupère les
  blocs si un constructeur échoue et détruit les objets encore actifs à sa
  destruction. `PoolResource` est une vue déplaçable non propriétaire.
- **Utilitaires** : `Timer` mesure des durées avec une horloge monotone.

## Exemple d'intégration

```cpp
#include "ecs/RenderSystem.hpp"

engine::World world;
engine::Renderer renderer(10, 4, '.');
engine::RenderSystem rendering(world, renderer);
auto entity = world.createEntity();
world.addComponent<engine::Position>(entity, {2, 1});
world.addComponent<engine::Sprite>(entity, {'@'});
rendering.update(0.016f);
renderer.render();
```

Les pointeurs de composants peuvent être invalidés par l'ajout ou la suppression
 d'un composant du même type. Ne pas modifier structurellement les composants
pendant `forEach` ; collecter les opérations et les appliquer après le parcours.
Les modules sont prévus pour un usage sur un seul thread. Le rendu reste textuel :
ce projet ne fournit pas de backend graphique, audio ou physique.

Les tests vérifient le cycle de vie ECS, le recyclage des identifiants, le rendu,
les entrées, l'alignement mémoire, le nettoyage des objets et les exceptions de
construction.
