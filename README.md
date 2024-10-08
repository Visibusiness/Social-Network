# Tema 3 - Structuri de Date și Algoritmi
### Popa Filip-Andrei & Vișănescu Bogdan-Emilian
### ~ 313CAb 2023-2024 ~
```
Echipa tema 3 SD:
filip_andrei.popa
bogdan.visanescu
```

## Tema constă în implementarea a trei taskuri diferite:
## Task 1 (Rețea de prietenie):
Am implementat rețeaua de prieteni folosind o structura de graf, care conține un vector de liste dublu înlănțuite, câte una pentru fiecare nod din graf. Lista cu indecele i va conține nodurile j cu proprietatea că exista muchie între nodul i si nodul j.
Pentru comenzile primite facem următoarele:
* pentru "add"/"remove": adăugam/ștergem o muchie în/din graf (adica introducem/scoatem nodul i in lista cu ordinul j  si nodul j in lista cu ordinul i)
* pentru "suggestions": căutăm vecinii vecinilor care nu sunt vecini ai unui nod cu indexul dat
* pentru "common": căutăm vecinii comuni ale două noduri
* pentru "friends": calculăm numărul de vecini ai unui nod, adică dimensiunea listei din structura de graf cu indexul nodului
* pentru "popular": calculăm numărul de vecini ai vecinilor unui nod dat
* pentru "distance": am implementat funcția get_distance(), care calculează distanța dintre 2 noduri din graf și este implementată astfel:
    ```
    1. Considerăm vectorul in_use[], care va funcționa precum o coadă (adugăm pe poziția last și primul element adugat va fi pe poziția first). Coada este considerată ca fiind goală când first>last. La început, coada conține doar nodul din care începem parcurgerea.
    2. Considerăm vectorul distance[], adică distanța de la nodul inițial la fiecare nod al grafului. (cu convenția că distance[x]=0 dacă si nu mai dacă nodul x nu a fost încă vizitat).
    3. Parcurgem în lățime graful: scoatem un nod din coadă și ii adăugăm toți vecinii nevizitați. Distanța de la nodul inițial la vecini va fi cu 1 mai mare decât distanța până la nodul scos.
    4. Ne oprim când dăm de nodul căutat sau când coada este goală, adică tot graful a fost parcurs fără a găsi nodul căutat, caz în care nu există drum între cele două noduri.

## Task 2 (Postări și reposturi):
Structura de postări este implementată ca un arbore al cărui rădăcină este un nod fictiv, denumit posts->root. Postările vor fi fii direcți ai nodului root, în timp ce repostările sunt nepoții nodurilor care reprezintă postări.
    
Arborele este implementat astfel: pentru fiecare nod, câmpul node->data este o structură denumită din lipsă de inspirație tree_t, care conține: informațiile referitoare la postare, un pointer către nodul tată din arbore și o listă de pointeri la nodurile care sunt fii direcți în arbore.

Pentru comenzile primite facem următoarele:
* pentru "create": adăugam un fiu nodului root.
* pentru "repost": căutăm nodul cu id-ul dat și îi adăugam un fiu.
* pentru "delete": căutăm nodul cu id-ul dat și îl ștergem din arbore.
* pentru "get-reposts": apelăm funcția get_reposts() care parcurgere arborele în preordine, plecând din nodul cu id-ul dat.
* pentru "like": căutăm nodul cu id-ul dat în arbore și îi adăugam un like în lista post_info->like, care conține noduri de tip like_t, care rețin id-urile celor care au dat like/dislike și dacă au dat like sau dislike.
* pentru "get-likes": apelăm funcția get_likes() care parcurge lista precizată anterior și calculează doar numărul de like-uri (nu și de dislike-uri).
* pentru "ratio": apelăm funcția find_most_liked_id() care parcurge subarborele care reprezintă repostările postării căruia ni se dă id-ul și calculează pentru fiecare repostare numărul de likeuri, apoi updatează most_likes și most_liked_id dacă este cazul.

## Task 3 (Social Media)
Acest task se bazează pe structurile implementate la celelalte două taskuri.

Comenzile sunt următoarele:
* "feed": parcurgere toate postările care nu sunt reposturi (adică fii direcți ai nodului root) și le afișează pe primele feed_size care sunt postate de prieteni ai utilizatorului cu id-ul dat.
* "view-profile": parcurge toate postările și repostările și le afișează pe cele facute de utilizatorului cu id-ul dat.
* "friend-repost": caută toate repostările unei postări și le afișează pe cele facute de prietenii utilizatorul cu id-ul dat.
* "common-group": apelează funcția maximal_clique(), care:
    ```
    1. pleacă cu o mulțime care conține doat utilizatorul cu id-ul dat;
    2. folosind cilque_backtracking() adaugă sau nu un utilizator în mulțimea curentă, iar adăugare are loc doar dacă el este prieten cu toți ceilalți utilizatori din mulțimea curentă;
    3. după ce am parcurs toți utilizatorii, am generat o clică validă, deci o actualizăm pe cea maximă dacă este cazul.
    ```