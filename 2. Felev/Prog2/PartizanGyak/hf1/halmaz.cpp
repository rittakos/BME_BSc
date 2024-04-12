// kapsz két fájlnevet, a fájlokban valós számok vannak
// mondd meg, melyik számok szerepeltek mindkét fájlban!
// https://infoc.eet.bme.hu/gy09/#4

#include <iostream>

struct Halmaz
{
    int db;
    double* adat;
};

void halmaz_init(Halmaz& h)
{
    h.db = 0;
	h.adat = NULL;
}

void halmaz_felszabadit(Halmaz& h)
{
	delete[] h.adat;
}

int halmaz_hol_van(Halmaz const& h, double mi)
{
	int min = 0;
	int max = h.db - 1;
	int idx;

	while (min != max)
	{
		idx = (min + max) / 2;
		if (h.adat[idx] == mi)
			return idx;
		if (h.adat[idx] < mi)
			min = idx + 1;
		else
			max = idx - 1;
	}
    return -1;         /* ha sehol nem talaltuk */
}

bool halmaz_benne_van_e(Halmaz const& h, double mi)
{
    return halmaz_hol_van(h, mi) != -1;
}

void Insert(Halmaz &h, int idx, double item)
{
	Halmaz temp = halmaz_init;
	temp = h;

	++h.db;
	h.adat = new double[h.db];

	int id;
	for (id = 0; id < idx; ++id)
		h[id] = temp[id];
	h[id + 1] = item;
	for (; id < h.db - 1; ++id)
		h[id + 1] = temp[id];
	halmaz_felszabadit(temp);
}

void halmaz_betesz(Halmaz& h, double mit)
{
    if (halmaz_benne_van_e(h, mit))
        return;
    
	if (mit < h.adat[0])
		Insert(h, 0, mit);
	else if (mit > h.adat[h.db - 1])
		Insert(h, h.db, mit);
	else
		for (int idx = 0; idx < h.db - 1; ++idx)
		{
			if (mit > h.adat[idx] && mit < h.adat[idx + 1])
				Insert(h, idx + 1, mit);
		}
}

void halmaz_kivesz(Halmaz& h, double mit)
{
    int index = halmaz_hol_van(h, mit);
    if (index == -1)
        return;
    for (int i = index; i < h.db - 1; ++i)
        h.adat[i] = h.adat[i+1];

	Halmaz temp = halmaz_init;
	temp = h;

	--h.db;
	h.adat = new double[h.db];

	for (id = 0; id < index; ++id)
		h[id] = temp[id];
	for (; id < h.db + 1; ++id)
		h[id - 1] = temp[id];
	halmaz_felszabadit(temp);
}

void halmaz_kiir(Halmaz const& h)
{
    for (int i = 0; i < h.db; ++i)
        std::cout << h.adat[i] << std::endl;
}

Halmaz halmaz_metszet(Halmaz const& egyik, Halmaz const& masik)
{
    Halmaz eredmeny;
    halmaz_init(eredmeny);

	eredmeny = egyik;

	int m = 0;
	int n = 0;
	while (m < egyik.db && n < masik.db)
	{
		if (egyik.adat[m] == masik.adat[n])
			halmaz_betesz(eredmeny, egyik.adat[m]);
		else if (egyik.adat[m] < masik.adat[n])
			++m;
		else
			++n;

	}

    return eredmeny;
}

Halmaz halmaz_beolvas(const char * fajlnev)
{
    Halmaz eredmeny;
    halmaz_init(eredmeny);

    FILE * fp = fopen(fajlnev, "r");
    // ha fp == NULL, nem tudunk mit csinálni
    double d;
    while (fscanf(fp, "%lf", &d) == 1)
    {
        halmaz_betesz(eredmeny, d);
    }

    fclose(fp);
    return eredmeny;
}


void fajlok_metszete(const char *elso_parameter, const char *masodik_parameter)
{
    Halmaz egyik = halmaz_beolvas(elso_parameter);
    Halmaz masik = halmaz_beolvas(masodik_parameter);

    Halmaz metszet = halmaz_metszet(egyik, masik);

    halmaz_kiir(metszet);

    halmaz_felszabadit(egyik);
    halmaz_felszabadit(masik);
    halmaz_felszabadit(metszet);
}
