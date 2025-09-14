import pandas as pd

# Construct module structure for both degrees based on extracted data
# BA Informatik 2022
informatik_2022 = {
    "STEOP": {
        "Programmierung 1": 6,
        "Technische Grundlagen der Informatik": 6,
        "Mathematische Grundlagen der Informatik 1": 6,
    },
    "Informatik Core": {
        "Theoretische Informatik": 6,
        "Programmierung 2": 6,
        "Modellierung": 6,
        "Betriebssysteme": 6,
        "Algorithmen & Datenstrukturen": 6,
        "Intelligente & Datenbanksysteme": 9,
        "Programmiersprachen & -konzepte": 6,
        "Software Engineering 1": 6,
        "Netzwerktechnologien": 9,
        "Software Engineering 2": 6,
        "Rechtliche & gesellschaftliche Grundlagen": 6,
        "Mensch-Computer-Interaktion": 9,
    },
    "Mathematik": {
        "Mathematische Grundlagen 2": 6,
        "Numerical Computing": 6,
        "Einführende Statistik": 6,
        "Mathematische Modellierung": 6,
    },
    "Wahlfach/Spezialisierung": {
        "Vertiefung": 30,
        "Erweiterung": 15,
    },
    "Bachelorarbeit & Praktikum": {
        "Softwarepraktikum & Bachelorarbeit": 12,
    },
}

# BA Wirtschaftsinformatik 2016
winfo_2016 = {
    "STEOP": {
        "Programmierung 1": 6,
        "Technische Grundlagen der Informatik": 6,
        "Mathematische Grundlagen der Informatik 1": 6,
    },
    "Informatik Core": {
        "Theoretische Informatik": 6,
        "Programmierung 2": 6,
        "Algorithmen & Datenstrukturen": 6,
        "Intelligente & Datenbanksysteme": 9,
        "Netzwerktechnologien": 6,
        "Software Engineering 1": 6,
        "Software Engineering 2": 6,
        "Mensch-Computer-Interaktion": 9,
    },
    "Mathematik": {
        "Mathematische Grundlagen 2": 6,
        "Einführende Statistik": 6,
        "Mathematische Modellierung": 6,
    },
    "Wirtschaftsinformatik": {
        "Grundlagen Winfo & BWL": 8,
        "Modellierung": 6,
        "Enterprise Architecture & IT-Sicherheit": 6,
        "Enterprise Information Systems": 6,
        "Distributed Systems Engineering": 6,
        "Information Management & Systems Engineering": 6,
        "Rechtliche & gesellschaftliche Grundlagen": 6,
    },
    "Wirtschaftswissenschaften": {
        "Volkswirtschaftslehre": 5,
        "Vertiefung BWL": 14,
    },
    "Wahlfach": {
        "Wahlfach": 15,
    },
    "Bachelorarbeit & Praktikum": {
        "Softwarepraktikum & Bachelorarbeit": 12,
    },
}

# Build comparison DataFrame (flattening categories)
def flatten_modules(degree_dict, degree_name):
    rows = []
    for cat, modules in degree_dict.items():
        for m, ects in modules.items():
            rows.append({"Degree": degree_name, "Category": cat, "Module": m, "ECTS": ects})
    return rows

df_informatik = pd.DataFrame(flatten_modules(informatik_2022, "Informatik 2022"))
df_winfo = pd.DataFrame(flatten_modules(winfo_2016, "Wirtschaftsinformatik 2016"))
df_all = pd.concat([df_informatik, df_winfo], ignore_index=True)

# Display the comparison
print("Curriculum Comparison - BA Informatik 2022 vs BA Wirtschaftsinformatik 2016")
print("="*80)
print(df_all.to_string(index=False))

# Summary statistics
print("\n\nSummary by Degree:")
print("="*40)
summary_by_degree = df_all.groupby('Degree')['ECTS'].sum()
print(summary_by_degree)

print("\n\nSummary by Category:")
print("="*40)
summary_by_category = df_all.groupby(['Degree', 'Category'])['ECTS'].sum().unstack(fill_value=0)
print(summary_by_category)

print("\n\nCategory Totals Across Both Degrees:")
print("="*40)
category_totals = df_all.groupby('Category')['ECTS'].sum().sort_values(ascending=False)
print(category_totals)