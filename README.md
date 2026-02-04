# farmacia-web
Sistema de farmácia desenvolvido em HTML, CSS e JavaScript, com consumo da API ViaCEP para preenchimento automático de endereço, focado em organização, usabilidade e estrutura frontend escalável.

❗A aplicação está publicada e acessível em ambiente real:
🔗 https://project-farmacia-web.vercel.app

Projeto desenvolvido com foco na construção de uma interface web para um sistema de farmácia, aplicando boas práticas de organização, usabilidade e consumo de API externa no frontend.

O sistema simula funcionalidades comuns de um ambiente comercial, incluindo formulários inteligentes e navegação intuitiva.

📌 Visão Geral

Este projeto tem como objetivo consolidar conhecimentos em desenvolvimento web frontend, com destaque para:
- Estruturação semântica de páginas
- Organização modular de arquivos
- Consumo de API externa para automação de formulários
- Experiência do usuário (UX)

Toda a aplicação é executada no navegador, sem backend ou persistência em banco de dados.

Tecnologias Utilizadas
- **HTML5** — Estrutura das páginas
- **CSS3** — Estilização e layout
- **JavaScript (Vanilla)** — Lógica e interações no frontend
- **API ViaCEP** — Preenchimento automático de endereço via CEP
- **Normalize.css** — Padronização entre navegadores

Consumo de API

O projeto realiza consumo da **API pública ViaCEP**, permitindo o preenchimento automático de campos de endereço a partir do CEP informado pelo usuário.

Funcionalidade implementada com:
- `fetch API`
- Requisições HTTP assíncronas
- Manipulação dinâmica do DOM

Esse recurso melhora a experiência do usuário e reduz erros de preenchimento em formulários.

Funcionalidades
- Página inicial com layout de sistema de farmácia
- Navegação por categorias de produtos
- Páginas temáticas (ex: cosméticos)
- Formulários de cadastro simulados
- Preenchimento automático de endereço via CEP (API ViaCEP)

> ⚠️ Observação: os formulários não realizam envio de dados para servidor ou banco de dados.

Projeto desenvolvido com fins educacionais, visando:
- Aplicar conceitos fundamentais de desenvolvimento web
- Praticar consumo de API no frontend
- Desenvolver interfaces organizadas e funcionais
- Criar base para futura integração com backend e banco de dados
