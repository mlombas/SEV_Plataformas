#include "Space.h"
#include <algorithm>

Space::Space(float gravity){
	this->gravity = gravity;
	dynamicActors.clear();
	staticActors.clear();
}

void Space::addDynamicActor(Actor* actor){
	dynamicActors.push_back(actor);
}

void Space::addStaticActor(Actor* actor){
	staticActors.push_back(actor);
}

void Space::removeDynamicActor(Actor* actor){
	dynamicActors.remove(actor);
}

void Space::removeStaticActor(Actor* actor){
	staticActors.remove(actor);
}

void Space::update(){
	for (auto const& actor : dynamicActors) {
		actor->vy = actor->vy + gravity;
		// máxima velocidad de caída por gravedad
		actor->vy = std::min(actor->vy, 20.0f);

		actor->collisionDown = false;

		// MoverDerecha / izquierda
		updateMoveRight(actor);
		updateMoveLeft(actor);
		updateMoveDown(actor);
		updateMoveTop(actor);
	}
}

void Space::updateMoveRight(Actor* dynamicAct){
	if (dynamicAct->vx > 0) {
		int possibleMovement = dynamicAct->vx;
		// El mejor "idealmente" vx partimos de ese

		for (auto const& staticAct : staticActors) {
			int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			int topDynamic = dynamicAct->y - dynamicAct->height / 2;
			int downDynamic = dynamicAct->y + dynamicAct->height / 2;

			int leftStatic = staticAct->x - staticAct->width / 2;
			int topStatic = staticAct->y - staticAct->height / 2;
			int downStatic = staticAct->y + staticAct->height / 2;

			// Alerta!, Elemento estático en la trayectoria.
			if ((rightDynamic + dynamicAct->vx) >= leftStatic
					&& rightDynamic <= leftStatic
					&& topStatic < downDynamic
					&& downStatic > topDynamic) {

				// Comprobamos si la distancia al estático es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement >= leftStatic - rightDynamic) {
					// La distancia es MENOR que nuestro movimiento posible
					// Tenemos que actualizar el movimiento posible a uno menor
					possibleMovement = leftStatic - rightDynamic;
				}
			}
		}
		// Ya se han comprobado todos los estáticos
		dynamicAct->x = dynamicAct->x + possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->vx = possibleMovement;
	}
}

void Space::updateMoveLeft(Actor* dynamicAct){
	if (dynamicAct->vx < 0) {
		int possibleMovement = dynamicAct->vx;
		// El mejor "idealmente" vx partimos de ese

		for (auto const& staticAct : staticActors) {
			int leftDynamic = dynamicAct->x - dynamicAct->width / 2;
			int topDynamic = dynamicAct->y - dynamicAct->height / 2;
			int downDynamic = dynamicAct->y + dynamicAct->height / 2;

			int rightStatic = staticAct->x + staticAct->width / 2;
			int topStatic = staticAct->y - staticAct->height / 2;
			int downStatic = staticAct->y + staticAct->height / 2;

			// Alerta!, Elemento estático en la trayectoria.
			if ((leftDynamic + dynamicAct->vx) <= rightStatic
					&& leftDynamic >= rightStatic
					&& topStatic < downDynamic
					&& downStatic > topDynamic) {

				// Comprobamos si la distancia al estático es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement <= rightStatic - leftDynamic) {
					// La distancia es MENOR que nuestro movimiento posible
					// Tenemos que actualizar el movimiento posible a uno menor
					possibleMovement = rightStatic - leftDynamic;
				}

			}

		}
		// Ya se han comprobado todos los estáticos
		dynamicAct->x = dynamicAct->x + possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->vx = possibleMovement;
	}
} 

void Space::updateMoveDown(Actor* dynamicAct) {
    if (dynamicAct->vy > 0) {
        int possibleMovement = dynamicAct->vy;
        // El mejor "idealmente" vy partimos de ese

        for (auto const& staticAct : staticActors) {
            int topDynamic = dynamicAct->y - dynamicAct->height / 2;
            int downDynamic = dynamicAct->y + dynamicAct->height / 2;
            int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
            int leftDynamic = dynamicAct->x - dynamicAct->width / 2;
         
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
            int rightStatic = staticAct->x + staticAct->width / 2;
            int leftStatic = staticAct->x - staticAct->width / 2;

            // Alerta!, Elemento estático en la trayectoria.
            if ((downDynamic + dynamicAct->vy) >= topStatic
                && topDynamic < downStatic
                && leftDynamic < rightStatic
                && rightDynamic > leftStatic) {

                // Comprobamos si la distancia al estático es menor
                // que nuestro movimientoPosible actual
                if (possibleMovement >= topStatic - downDynamic) {
                    // La distancia es MENOR que nuestro movimiento posible
                    // Tenemos que actualizar el movimiento posible a uno menor
                    possibleMovement = topStatic - downDynamic;
					dynamicAct->collisionDown = true;
                }
            }
        }
        // Ya se han comprobado todos los estáticos
        dynamicAct->y = dynamicAct->y + possibleMovement;
        // Restringir la velocidad actual (opcional)
        dynamicAct->vy = possibleMovement;
    }
}

void Space::updateMoveTop(Actor* dynamicAct) {
    if (dynamicAct->vy < 0) {
        int possibleMovement = dynamicAct->vy;
        // El mejor "idealmente" vy partimos de ese

        for (auto const& staticAct : staticActors) {
            int topDynamic = dynamicAct->y - dynamicAct->height / 2;
            int downDynamic = dynamicAct->y + dynamicAct->height / 2;
            int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
            int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
            int rightStatic = staticAct->x + staticAct->width / 2;
            int leftStatic = staticAct->x - staticAct->width / 2;

            // Alerta!, Elemento estático en la trayectoria.
            if ((topDynamic + dynamicAct->vy) <= downStatic
                && downDynamic > topStatic
                && leftDynamic < rightStatic
                && rightDynamic > leftStatic) {

                // Comprobamos si la distancia al estático es menor
                // que nuestro movimientoPosible actual
                if (possibleMovement <= downStatic - topDynamic) {
                    // La distancia es MENOR que nuestro movimiento posible
                    // Tenemos que actualizar el movimiento posible a uno menor
                    possibleMovement = downStatic - topDynamic;
                }
            }
        }
        // Ya se han comprobado todos los estáticos
        dynamicAct->y = dynamicAct->y + possibleMovement;
        // Restringir la velocidad actual (opcional)
        dynamicAct->vy = possibleMovement;
    }
}
