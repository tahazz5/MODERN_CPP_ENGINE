# MODERN_CPP_ENGINE

Ce dépôt fournit un squelette minimal de moteur de jeu C++ moderne.

Des améliorations récentes incluent un **système de rendu** de base construit
au-dessus des modules ECS et mémoire existants. Vous pouvez désormais définir
les composants `Position` et `Sprite`, les attacher aux entités, et piloter un
`Renderer` simple via un `RenderSystem` pour produire un tampon d'image textuel.
Un nouvel ensemble de tests (`RenderingTests`) vérifie ce comportement.
