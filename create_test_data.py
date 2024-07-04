import random

names = ["Praia", "Pretoria", "Pyongyang", "Rabat", "Rangpur", "Reggane", "Reykjavík", "Riga",
         "Riyadh", "Rome", "Roseau", "Rostov-on-Don", "Sacramento", "Saint Petersburg", "Saint-Pierre",
         "Salt Lake City", "San Antonio", "San Diego", "San Francisco", "San Jose", "San José",
         "San Juan", "San Salvador", "Sana'a", "Santo Domingo", "Sapporo", "Sarajevo", "Saskatoon",
         "Seattle", "Ségou", "Seoul", "Seville", "Shanghai", "Singapore", "Skopje", "Sochi", "Sofia"]


def create_test_data(count):
    with open('measurements_test.txt', 'w') as fh:
        for i in range(int(count)):
            fh.write('{},{:.01f}\n'.format(random.choice(names), random.uniform(-10, 10)))

def main():
    random.seed(0xDEADBEEF)
    create_test_data(10000)

if __name__ == '__main__':
    main()
