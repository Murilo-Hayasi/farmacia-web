// cpf
function mascaraCPF(campo) {
  let v = campo.value.replace(/\D/g, ""); // remove tudo que não é número
  if (v.length > 11) v = v.slice(0, 11);


  if (v.length > 9)
    v = v.replace(/(\d{3})(\d{3})(\d{3})(\d{2})/, "$1.$2.$3-$4");
  else if (v.length > 6)
    v = v.replace(/(\d{3})(\d{3})(\d+)/, "$1.$2.$3");
  else if (v.length > 3)
    v = v.replace(/(\d{3})(\d+)/, "$1.$2");

  campo.value = v;
  campo.style.borderColor = v.length === 14 ? "limegreen" : "red";
}

function mascaraRG(campo) {
  let v = campo.value.replace(/\D/g, ""); // remove tudo que não é número
  if (v.length > 9) v = v.slice(0, 9);


  if (v.length > 7)
    v = v.replace(/(\d{2})(\d{3})(\d{3})(\d{1})/, "$1.$2.$3-$4");
  else if (v.length > 4)
    v = v.replace(/(\d{2})(\d{3})(\d+)/, "$1.$2.$3");
  else if (v.length > 1)
    v = v.replace(/(\d{2})(\d+)/, "$1.$2");

  campo.value = v;
  campo.style.borderColor = v.length === 12 ? "limegreen" : "red";
}

//telefone
function mascaraTelefone(campo) {
  let v = campo.value.replace(/\D/g, "");
  if (v.length > 11) v = v.slice(0, 11);

  if (v.length > 10)
    v = v.replace(/(\d{2})(\d{5})(\d{4})/, "($1) $2-$3");
  else if (v.length > 6)
    v = v.replace(/(\d{2})(\d{4})(\d+)/, "($1) $2-$3");
  else if (v.length > 2)
    v = v.replace(/(\d{2})(\d+)/, "($1) $2");

  campo.value = v;
  campo.style.borderColor = v.length >= 13 ? "limegreen" : "red";
}

// cep
function mascaraCEP(campo) {
  let v = campo.value.replace(/\D/g, "");
  if (v.length > 8) v = v.slice(0, 8);

  if (v.length > 5)
    v = v.replace(/(\d{5})(\d+)/, "$1-$2");

  campo.value = v;
  campo.style.borderColor = v.length === 9 ? "limegreen" : "red";
}

//cnpj
function mascaraCNPJ(campo) {
  let v = campo.value.replace(/\D/g, ""); // remove tudo que não é número
  if (v.length > 14) v = v.slice(0, 14);


  if (v.length > 13)
    v = v.replace(/(\d{2})(\d{3})(\d{3})(\d{4})(\d{2})/, "$1.$2.$3/$4-$5");
  else if (v.length > 8)
    v = v.replace(/(\d{2})(\d{3})(\d+)/, "$1.$2.$3");
  else if (v.length > 2)
    v = v.replace(/(\d{3})(\d+)/, "$1.$2");

  campo.value = v;
  campo.style.borderColor = v.length === 18 ? "limegreen" : "red";
}