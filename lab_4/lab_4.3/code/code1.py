import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import linear_kernel
# Пример данных об описании фильмов
data = {
    'title': ['The Graduate', '12 Angry Men', 'Women on the Verge of a Nervous Breakdown', 'Alien', 'A Hard Day’s Night', 'Toy Story','Bridesmaids','Le Samouraï','Pink Flamingos','Scenes From a Marriage'],
    'description': ['Mike Nichols’ indelible comedy of alienation is that rare thing, a movie that really does define a generation. That’s because there has never been another movie like it',
        'How elemental — and riveting — is this: an entire courtroom drama set inside the jury room, where Henry Fonda, as the only member of the jury',
        'You never forget your first. That may be how many American art-house habituésthink of Pedro Almodóvar’s riotous comedy.',
        'A smothering tentacled thingy attaches itself to an astronaut’s face. Several scenes later, an alien fetus erupts right out of his belly, and the cinema would never be the same',
        'The most transportive rock ’n’ roll movie ever made. Richard Lester, drawing on cutting-edge film techniques that are still bracing, fulfilled his assignment of directing a Beatles movie',
        'In the early ’80s, director John Lasseter tried to convince Disney to invest in CGI',
        'A decade has passed since “Bridesmaids” launched a thousand think pieces about the future of female-driven films, but Hollywood has yet to produce a funnier movie from any corner.',
        'Long before Tarantino, Jean-Pierre Melville obsessed about movies, admiring American directors and absorbing their codes. In the early ’50s,',
        'It was panned by Variety, which called it “one of the most vile, stupid and repulsive films ever made.',
        'In the ’50s and ’60s, Ingmar Bergman became the poster boy for the mystique of art-house cinema by filling his black-and-white movies with symbols, metaphors, dreams.'
    ]
}
# Создание DataFrame
movies = pd.DataFrame(data)
# Векторизация описания фильмов
tfidf = TfidfVectorizer(stop_words='english')
tfidf_matrix = tfidf.fit_transform(movies['description'])
# Вычисление косинусной схожести
cosine_sim = linear_kernel(tfidf_matrix, tfidf_matrix)
# Функция для получения рекомендаций
def get_recommendations(title, cosine_sim=cosine_sim):
    idx = movies[movies['title'] == title].index[0]
    sim_scores = list(enumerate(cosine_sim[idx]))
    sim_scores = sorted(sim_scores, key=lambda x: x[1],
reverse=True)
    sim_scores = sim_scores[1:2]
    movie_indices = [i[0] for i in sim_scores]
    return movies['title'].iloc[movie_indices], movies['description'].iloc[movie_indices]
# Пример использования
movie_title = input("Введите название фильма: ")
recommendation_title, recommendation_descr = get_recommendations(movie_title)
print("Рекомендуемый фильм:", recommendation_title.values[0])
print('Description:', recommendation_descr.values[0])
