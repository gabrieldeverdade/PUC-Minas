sessionStorage.setItem("isPesquisa", true);
const TMDB_ENDPOINT_BASE = 'https://api.themoviedb.org/3';
$(document).ready(function () {
  //sessionStorage.setItem("isPesquisa", true);
  if (sessionStorage.getItem("isPesquisa") == "true") {
    $.ajax({
      // Passar a URL ENDPOINT BASE + /movie/now_playing
      url: TMDB_ENDPOINT_BASE + "/search/movie",
      data: {
        api_key: "c2f4c89b537808c194cac27dae3a091e",
        query: sessionStorage.getItem("item"),
      },
    })
      // Receber o JSON
      .done(function (data) {
        let codigo_html = "";
        
        // Montar os cards
        for (i = 0; i < data.results.length; i++) {
          // Concatenar o código do Card com os dados do JSON
          titulo = data.results[i].title;
          imagem = "https://image.tmdb.org/t/p/w500" + data.results[i].poster_path;
          descricao = data.results[i].overview;
          id = data.results[i].id;

          codigo_html += `<div class="card mb-3" style="max-width: 700px;">
                <div class="row no-gutters">
                  <div class="col-md-4">
                    <img src="${imagem}" class="card-img" alt="${titulo}">
                  </div>
                  <div class="col-md-8">
                    <div class="card-body">
                      <h2 class="card-title">${titulo}</h2>
                      <p class="card-text">${descricao}</p>
                      <a href="https://www.themoviedb.org/movie/${id}-${titulo}" target="_blank" id="buttonc1" class="btn btn-primary">Saiba Mais</a>
                    </div>
                  </div>
                </div>
              </div>`;
        }
        // Repassar os cards para a página
        $("#pes").html(codigo_html);
        sessionStorage.setItem("item", "");
      });
  }

  $("#onpopulares").click(function () {sessionStorage.setItem("pop", true);});
  $("#oncinema").click(function () {sessionStorage.setItem("cin", true);});
  $("#onnovi").click(function () {sessionStorage.setItem("novi", true);});
  sessionStorage.setItem("cin", false);
  sessionStorage.setItem("pop", false);
  sessionStorage.setItem("novi", false);
  $("#btn_pesquisa").click(function () {
    //sessionStorage.setItem("isPesquisa", true);
    if (sessionStorage.getItem("isPesquisa")) {
      sessionStorage.setItem("item", $("#search").val());
    }
  });
});
