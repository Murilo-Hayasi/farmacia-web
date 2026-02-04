async function buscarCEP(campo) {
  const cep = campo.value.replace(/\D/g, '');

  if (cep.length !== 8) {
    campo.classList.add('input-invalido');
    return;
  }

  try {
    const resposta = await fetch(`https://viacep.com.br/ws/${cep}/json/`);
    const dados = await resposta.json();

    if (dados.erro) throw new Error('CEP não encontrado');

    document.getElementById('rua').value = dados.logradouro;
    document.getElementById('bairro').value = dados.bairro;
    document.getElementById('cidade').value = dados.localidade;
    document.getElementById('uf').value = dados.uf;

    campo.classList.add('input-valido');
    campo.classList.remove('input-invalido');
  } catch (e) {
    campo.classList.add('input-invalido');
    campo.classList.remove('input-valido');
    document.getElementById('rua').value = '';
    document.getElementById('bairro').value = '';
    document.getElementById('cidade').value = '';
    document.getElementById('uf').value = '';
  }
}


