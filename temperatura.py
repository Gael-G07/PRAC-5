import random

LIMITE = 30.0

def leer_temperatura():
    return round(random.uniform(20.0, 40.0), 1)

def main():
    temperatura = leer_temperatura()
    print(f"Temperatura: {temperatura} C")
    if temperatura > LIMITE:
        print("ALERTA: Encender motor")
    else:
        print("Temperatura normal: Apagar motor")

if __name__ == "__main__":
    main()