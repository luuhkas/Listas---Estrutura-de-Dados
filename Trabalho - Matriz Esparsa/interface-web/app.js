/*
 * Interface web para o programa C de matriz esparsa.
 *
 * O state local em JS espelha o estado da matriz para renderizar a tabela
 * visual e o SVG da estrutura interna. Toda operacao tambem eh enviada
 * para o programa C real (compilado a partir de matriz_esparsa.c), e a
 * saida do C aparece no painel inferior.
 */

const state = {
    rows: 0,
    cols: 0,
    values: [],
    operations: [],
    lastChange: null  // { x, y, kind: "insert" | "remove" } para animação
};

function sleep(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms));
}

const output = document.getElementById("output");
const sparseView = document.getElementById("sparseView");
const structureSvg = document.getElementById("structureSvg");
const structureHint = document.getElementById("structureHint");
const statSize = document.getElementById("statSize");
const statTotal = document.getElementById("statTotal");
const statFilled = document.getElementById("statFilled");
const statNodes = document.getElementById("statNodes");
const statAction = document.getElementById("statAction");
const denseBar = document.getElementById("denseBar");
const sparseBar = document.getElementById("sparseBar");
const denseBytes = document.getElementById("denseBytes");
const sparseBytes = document.getElementById("sparseBytes");
const denseRow = document.getElementById("denseRow");
const sparseRow = document.getElementById("sparseRow");
const comparisonVerdict = document.getElementById("comparisonVerdict");
const comparisonTip = document.getElementById("comparisonTip");

const API_URL = "http://127.0.0.1:8080/run";


function numberFrom(id) {
    return Number.parseInt(document.getElementById(id).value, 10);
}

function isInteger(value) {
    return Number.isInteger(value);
}

function setOutput(text) {
    output.textContent = text;
}

function countNonZeros() {
    let n = 0;
    for (let i = 0; i < state.rows; i++) {
        for (let j = 0; j < state.cols; j++) {
            if (state.values[i][j] !== 0) n++;
        }
    }
    return n;
}

function formatBytes(b) {
    if (b < 1024) return `${b} B`;
    if (b < 1024 * 1024) return `${(b / 1024).toFixed(1)} KB`;
    return `${(b / (1024 * 1024)).toFixed(2)} MB`;
}

function updateComparison() {
    if (state.rows <= 0) {
        denseBar.style.width = "0%";
        sparseBar.style.width = "0%";
        denseBytes.textContent = "—";
        sparseBytes.textContent = "—";
        denseRow.classList.remove("winner", "loser");
        sparseRow.classList.remove("winner", "loser");
        comparisonVerdict.innerHTML = "Crie uma matriz para ver a comparação.";
        comparisonTip.innerHTML = "Crie uma matriz para ver a análise detalhada.";
        return;
    }

    const r = countNonZeros();
    const m = state.rows;
    const n = state.cols;
    const totalCells = m * n;
    const dense = totalCells * 4;
    const sparseNodes = m + n + r + 1;
    const sparse = sparseNodes * 32;
    const max = Math.max(dense, sparse);
    const densityFraction = r / totalCells;
    const densityPct = (densityFraction * 100).toFixed(1);

    denseBar.style.width = (dense / max * 100).toFixed(1) + "%";
    sparseBar.style.width = (sparse / max * 100).toFixed(1) + "%";
    denseBytes.textContent = formatBytes(dense);
    sparseBytes.textContent = formatBytes(sparse);

    denseRow.classList.remove("winner", "loser");
    sparseRow.classList.remove("winner", "loser");

    if (sparse < dense) {
        sparseRow.classList.add("winner");
        denseRow.classList.add("loser");
        const ratio = (dense / sparse).toFixed(1);
        const economiaPct = ((1 - sparse / dense) * 100).toFixed(0);
        comparisonVerdict.innerHTML = `
            <strong>Esparsa vence:</strong> economiza ${economiaPct}% de memória (${ratio}× menor).
            Densidade da matriz: ${densityPct}% — abaixo do limite onde a esparsa compensa.
        `;
    } else if (dense < sparse) {
        denseRow.classList.add("winner");
        sparseRow.classList.add("loser");
        const ratio = (sparse / dense).toFixed(1);
        comparisonVerdict.innerHTML = `
            <strong>Densa vence neste caso:</strong> esparsa custa ${ratio}× mais memória.
            Densidade da matriz: ${densityPct}% — alta demais para compensar o overhead dos ponteiros.
            Em matrizes maiores com poucos não-zeros, a esparsa passa a vencer.
        `;
    } else {
        comparisonVerdict.innerHTML = `<strong>Empate técnico:</strong> ambas custam ${formatBytes(dense)}.`;
    }

    // ===== Análise detalhada (calculada) =====

    // 1. Para esse tamanho m×n, qual é o r máximo para esparsa compensar?
    //    (m + n + r + 1) × 32 < m × n × 4
    //    r < m×n/8 − m − n − 1
    const rMax = Math.floor(totalCells / 8 - m - n - 1);

    // 2. Mantendo a densidade atual, a partir de qual N (matriz N×N) compensa?
    //    N²(1 - 8d) > 16N + 8  →  bhaskara
    let nMin = null;
    if (densityFraction < 0.125) {
        const a = 1 - 8 * densityFraction;
        const delta = 288 - 256 * densityFraction;
        nMin = Math.ceil((16 + Math.sqrt(delta)) / (2 * a));
    }

    let tip = "<strong>Análise dinâmica:</strong> ";

    // Parte 1: análise para o tamanho atual
    if (rMax >= 1) {
        tip += `<p>Para uma matriz <code>${m} × ${n}</code>, a esparsa compensa quando ` +
               `<code>r ≤ ${rMax}</code>. ` +
               `Atualmente <code>r = ${r}</code> → <strong>${sparse < dense ? "esparsa" : (dense < sparse ? "densa" : "empate")}</strong> vence.</p>`;
    } else if (rMax === 0) {
        tip += `<p>Matriz <code>${m} × ${n}</code> é pequena demais: a esparsa só compensa com <code>r = 0</code> ` +
               `(matriz totalmente vazia), e mesmo assim por margem mínima.</p>`;
    } else {
        tip += `<p>Matriz <code>${m} × ${n}</code> é pequena demais para a esparsa compensar em qualquer cenário ` +
               `— o overhead das cabeças (m + n + 1 = ${m + n + 1} nós × 32 B = ${formatBytes((m + n + 1) * 32)}) ` +
               `já excede a matriz densa inteira (${formatBytes(dense)}).</p>`;
    }

    // Parte 2: a partir de qual tamanho compensa (mantendo densidade atual)
    if (densityFraction === 0) {
        tip += `<p>Para matrizes <strong>vazias</strong> (sem nenhum valor), a esparsa começa a vencer ` +
               `a partir de <code>${nMin} × ${nMin}</code>. ` +
               `Tente criar uma matriz desse tamanho ou maior!</p>`;
    } else if (densityFraction < 0.125) {
        tip += `<p>Mantendo a densidade atual de <code>${densityPct}%</code>, ` +
               `a esparsa começa a vencer em matrizes <strong>${nMin} × ${nMin}</strong> ou maiores ` +
               `(considerando matriz quadrada com a mesma proporção de não-zeros).</p>`;
    } else {
        tip += `<p>Com densidade <code>${densityPct}%</code> (≥ 12,5%), a esparsa ` +
               `<strong>não compensa em nenhum tamanho de matriz</strong> — ` +
               `independentemente de quão grande seja, o overhead dos ponteiros sempre vai superar. ` +
               `A densidade precisa cair abaixo de <code>12,5%</code> para que a esparsa ganhe.</p>`;
    }

    comparisonTip.innerHTML = tip;
}

function updateStats(action) {
    const r = countNonZeros();
    statSize.textContent = state.rows > 0 ? `${state.rows} x ${state.cols}` : "—";
    statTotal.textContent = state.rows > 0 ? state.rows * state.cols : "0";
    statFilled.textContent = r;
    statNodes.textContent = state.rows > 0 ? state.rows + state.cols + r + 1 : "0";
    if (action !== undefined) statAction.textContent = action;
    updateComparison();
}

function updateSparseView() {
    const values = [];
    for (let i = 0; i < state.rows; i++) {
        for (let j = 0; j < state.cols; j++) {
            if (state.values[i][j] !== 0) {
                values.push({ row: i, col: j, value: state.values[i][j] });
            }
        }
    }

    if (values.length === 0) {
        sparseView.textContent = "Nenhum valor diferente de zero.";
        return;
    }

    sparseView.innerHTML = values
        .map((v) => `<div><strong>(${v.row}, ${v.col})</strong><span>${v.value}</span></div>`)
        .join("");
}

function hasMatrix() {
    if (state.rows <= 0 || state.cols <= 0) {
        setOutput("Crie uma matriz primeiro.");
        return false;
    }
    return true;
}

function validPosition(x, y) {
    return isInteger(x) && isInteger(y) && x >= 0 && y >= 0 && x < state.rows && y < state.cols;
}

function updateStructureHint() {
    if (state.rows > 0) {
        structureHint.textContent = `Linhas 0-${state.rows - 1}, colunas 0-${state.cols - 1}`;
    } else {
        structureHint.textContent = "Crie uma matriz para visualizar.";
    }
}

/* ============================================================
 * SVG da estrutura interna (lista cruzada de Ziviani)
 * ============================================================ */

function renderStructure() {
    if (state.rows <= 0) {
        structureSvg.innerHTML = `<p class="placeholder">A estrutura aparece aqui apos criar uma matriz.</p>`;
        return;
    }

    const boxW = 110;
    const boxH = 52;
    const gapX = 50;
    const gapY = 45;
    const marginX = 70;
    const marginY = 70;
    const extraBottom = 30;
    const extraRight = 40;

    const cellW = boxW + gapX;
    const cellH = boxH + gapY;

    const totalW = marginX * 2 + (state.cols + 1) * cellW - gapX + extraRight;
    const totalH = marginY * 2 + (state.rows + 1) * cellH - gapY + extraBottom;

    // Funções de posição (canto superior esquerdo da caixa)
    const x = (col) => marginX + (col + 1) * cellW;  // col = -1 -> principal, col = j -> coluna j
    const y = (row) => marginY + (row + 1) * cellH;  // row = -1 -> linha topo (cabeças col), row = i -> linha i

    // Principal: (col=-1, row=-1)
    const xPrincipal = marginX;
    const yPrincipal = marginY;

    // Helpers
    const cx = (col) => (col === -1 ? xPrincipal : x(col)) + boxW / 2;
    const cy = (row) => (row === -1 ? yPrincipal : y(row)) + boxH / 2;
    const left = (col) => (col === -1 ? xPrincipal : x(col));
    const top = (row) => (row === -1 ? yPrincipal : y(row));
    const right = (col) => left(col) + boxW;
    const bottom = (row) => top(row) + boxH;

    // Encontra próximo não-zero na linha i, a partir da coluna j+1
    const nextInRow = (i, j) => {
        for (let k = j + 1; k < state.cols; k++) {
            if (state.values[i][k] !== 0) return k;
        }
        return null;
    };
    // Encontra próximo não-zero na coluna j, a partir da linha i+1
    const nextInCol = (i, j) => {
        for (let k = i + 1; k < state.rows; k++) {
            if (state.values[k][j] !== 0) return k;
        }
        return null;
    };
    // Encontra primeiro não-zero na linha i
    const firstInRow = (i) => {
        for (let k = 0; k < state.cols; k++) {
            if (state.values[i][k] !== 0) return k;
        }
        return null;
    };
    // Encontra primeiro não-zero na coluna j
    const firstInCol = (j) => {
        for (let k = 0; k < state.rows; k++) {
            if (state.values[k][j] !== 0) return k;
        }
        return null;
    };

    let svg = '';
    svg += `<svg viewBox="0 0 ${totalW} ${totalH}" xmlns="http://www.w3.org/2000/svg" preserveAspectRatio="xMidYMid meet">`;
    svg += `
      <defs>
        <marker id="ar" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="6" markerHeight="6" orient="auto">
          <path d="M 0 0 L 10 5 L 0 10 z" fill="#38bdf8"/>
        </marker>
        <marker id="arY" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="6" markerHeight="6" orient="auto">
          <path d="M 0 0 L 10 5 L 0 10 z" fill="#f59e0b"/>
        </marker>
        <marker id="arG" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="5" markerHeight="5" orient="auto">
          <path d="M 0 0 L 10 5 L 0 10 z" fill="#64748b"/>
        </marker>
        <linearGradient id="gradPr" x1="0%" y1="0%" x2="100%" y2="100%">
          <stop offset="0%" stop-color="#1e1b4b" />
          <stop offset="100%" stop-color="#3b0764" />
        </linearGradient>
        <linearGradient id="gradHd" x1="0%" y1="0%" x2="100%" y2="100%">
          <stop offset="0%" stop-color="#1a1206" />
          <stop offset="100%" stop-color="#451a03" />
        </linearGradient>
        <linearGradient id="gradNd" x1="0%" y1="0%" x2="100%" y2="100%">
          <stop offset="0%" stop-color="#0c1f2e" />
          <stop offset="100%" stop-color="#0a1a26" />
        </linearGradient>
        <style>
          .nd { fill: url(#gradNd); stroke: #38bdf8; stroke-width: 1.5; }
          .hd { fill: url(#gradHd); stroke: #f59e0b; stroke-width: 1.5; }
          .pr { fill: url(#gradPr); stroke: #a855f7; stroke-width: 2; }
          .lb { fill: #f1f5f9; font-family: 'JetBrains Mono', Menlo, monospace; font-size: 11px; font-weight: 600; }
          .sm { fill: #94a3b8; font-family: 'JetBrains Mono', Menlo, monospace; font-size: 10px; }
          .vl { fill: #10b981; font-family: 'JetBrains Mono', Menlo, monospace; font-size: 14px; font-weight: bold; }
          .em { fill: #64748b; font-family: 'JetBrains Mono', Menlo, monospace; font-size: 10px; font-style: italic; }
          .ar { stroke: #38bdf8; stroke-width: 1.4; fill: none; opacity: 0.9; }
          .arL { stroke: #f59e0b; stroke-width: 1.5; fill: none; stroke-dasharray: 5 3; opacity: 0.85; }
          .arS { stroke: #94a3b8; stroke-width: 1.5; fill: none; opacity: 0.9; }
          .arS-label { fill: #94a3b8; font-family: 'JetBrains Mono', Menlo, monospace; font-size: 10px; font-style: italic; }
        </style>
      </defs>
    `;

    // ===== Caixas =====

    // Principal (-1, -1)
    svg += `<rect id="el-principal" x="${xPrincipal}" y="${yPrincipal}" width="${boxW}" height="${boxH}" class="pr" rx="3"/>`;
    svg += `<text x="${xPrincipal + boxW / 2}" y="${yPrincipal + boxH / 2 - 4}" class="lb" text-anchor="middle">principal</text>`;
    svg += `<text x="${xPrincipal + boxW / 2}" y="${yPrincipal + boxH / 2 + 10}" class="sm" text-anchor="middle">(-1, -1)</text>`;

    // Cabeças de coluna (texto "(vazia)" só com loop maior abaixo)
    for (let j = 0; j < state.cols; j++) {
        svg += `<rect id="el-cabcol-${j}" x="${x(j)}" y="${y(-1)}" width="${boxW}" height="${boxH}" class="hd" rx="3"/>`;
        svg += `<text x="${x(j) + boxW / 2}" y="${y(-1) + boxH / 2 - 4}" class="lb" text-anchor="middle">cab_col_${j}</text>`;
        svg += `<text x="${x(j) + boxW / 2}" y="${y(-1) + boxH / 2 + 10}" class="sm" text-anchor="middle">(-1, ${j})</text>`;
    }

    // Cabeças de linha
    for (let i = 0; i < state.rows; i++) {
        svg += `<rect id="el-cablin-${i}" x="${x(-1)}" y="${y(i)}" width="${boxW}" height="${boxH}" class="hd" rx="3"/>`;
        svg += `<text x="${x(-1) + boxW / 2}" y="${y(i) + boxH / 2 - 4}" class="lb" text-anchor="middle">cab_lin_${i}</text>`;
        svg += `<text x="${x(-1) + boxW / 2}" y="${y(i) + boxH / 2 + 10}" class="sm" text-anchor="middle">(${i}, -1)</text>`;
    }

    // Nós reais
    for (let i = 0; i < state.rows; i++) {
        for (let j = 0; j < state.cols; j++) {
            const v = state.values[i][j];
            if (v === 0) continue;
            const isNew = state.lastChange && state.lastChange.kind === "insert"
                && state.lastChange.x === i && state.lastChange.y === j;
            const rectClass = isNew ? "nd node-new" : "nd";
            svg += `<rect id="el-node-${i}-${j}" x="${x(j)}" y="${y(i)}" width="${boxW}" height="${boxH}" class="${rectClass}" rx="3"/>`;
            svg += `<text x="${x(j) + boxW / 2}" y="${y(i) + boxH / 2 - 4}" class="sm" text-anchor="middle">(${i}, ${j})</text>`;
            svg += `<text x="${x(j) + boxW / 2}" y="${y(i) + boxH / 2 + 11}" class="vl" text-anchor="middle">${v}</text>`;
        }
    }

    // ===== Setas azuis (próximo na lista) =====

    // principal -> cab_col_0
    svg += `<path d="M ${right(-1)} ${cy(-1)} L ${left(0)} ${cy(-1)}" class="ar" marker-end="url(#ar)"/>`;
    // principal -> cab_lin_0
    svg += `<path d="M ${cx(-1)} ${bottom(-1)} L ${cx(-1)} ${top(0)}" class="ar" marker-end="url(#ar)"/>`;

    // Entre cabeças de coluna consecutivas
    for (let j = 0; j < state.cols - 1; j++) {
        svg += `<path d="M ${right(j)} ${cy(-1)} L ${left(j + 1)} ${cy(-1)}" class="ar" marker-end="url(#ar)"/>`;
    }
    // Entre cabeças de linha consecutivas
    for (let i = 0; i < state.rows - 1; i++) {
        svg += `<path d="M ${cx(-1)} ${bottom(i)} L ${cx(-1)} ${top(i + 1)}" class="ar" marker-end="url(#ar)"/>`;
    }

    // Setas DIREITA (linhas com nós)
    for (let i = 0; i < state.rows; i++) {
        // cab_lin_i -> primeiro nó da linha
        const first = firstInRow(i);
        if (first !== null) {
            svg += `<path d="M ${right(-1)} ${cy(i)} L ${left(first)} ${cy(i)}" class="ar" marker-end="url(#ar)"/>`;
            // Setas entre nós consecutivos na linha
            let cur = first;
            while (true) {
                const nxt = nextInRow(i, cur);
                if (nxt === null) break;
                svg += `<path d="M ${right(cur)} ${cy(i)} L ${left(nxt)} ${cy(i)}" class="ar" marker-end="url(#ar)"/>`;
                cur = nxt;
            }
        }
    }

    // Setas ABAIXO (colunas com nós)
    for (let j = 0; j < state.cols; j++) {
        const first = firstInCol(j);
        if (first !== null) {
            svg += `<path d="M ${cx(j)} ${bottom(-1)} L ${cx(j)} ${top(first)}" class="ar" marker-end="url(#ar)"/>`;
            let cur = first;
            while (true) {
                const nxt = nextInCol(cur, j);
                if (nxt === null) break;
                svg += `<path d="M ${cx(j)} ${bottom(cur)} L ${cx(j)} ${top(nxt)}" class="ar" marker-end="url(#ar)"/>`;
                cur = nxt;
            }
        }
    }

    // ===== Setas amarelas (voltas circulares) =====

    // cab_col_(n-1) -> principal (volta no topo)
    {
        const lastCol = state.cols - 1;
        const aboveY = marginY - 30;
        svg += `<path d="M ${cx(lastCol)} ${top(-1)} L ${cx(lastCol)} ${aboveY} L ${cx(-1)} ${aboveY} L ${cx(-1)} ${top(-1)}" class="arL" marker-end="url(#arY)"/>`;
        svg += `<text x="${(cx(-1) + cx(lastCol)) / 2}" y="${aboveY - 8}" text-anchor="middle" font-family="Menlo,monospace" font-size="11" fill="#fbbf24">cab_col_${lastCol}.direita → principal</text>`;
    }

    // cab_lin_(m-1) -> principal (volta na esquerda)
    {
        const lastLin = state.rows - 1;
        const leftX = marginX - 30;
        svg += `<path d="M ${left(-1)} ${cy(lastLin)} L ${leftX} ${cy(lastLin)} L ${leftX} ${cy(-1)} L ${left(-1)} ${cy(-1)}" class="arL" marker-end="url(#arY)"/>`;
        svg += `<text x="${leftX - 8}" y="${(cy(-1) + cy(lastLin)) / 2}" text-anchor="middle" font-family="Menlo,monospace" font-size="11" fill="#fbbf24" transform="rotate(-90 ${leftX - 8} ${(cy(-1) + cy(lastLin)) / 2})">cab_lin_${lastLin}.abaixo → principal</text>`;
    }

    // Volta direita: último nó de cada linha -> cab_lin_i
    for (let i = 0; i < state.rows; i++) {
        const last = lastInRow(i);
        if (last !== null) {
            const goY = cy(i) - boxH / 2 - 10;
            svg += `<path d="M ${right(last)} ${cy(i)} L ${right(last) + 15} ${cy(i)} L ${right(last) + 15} ${goY} L ${cx(-1)} ${goY} L ${cx(-1)} ${top(i)}" class="arL" marker-end="url(#arY)"/>`;
        }
    }

    // Volta abaixo: último nó de cada coluna -> cab_col_j
    for (let j = 0; j < state.cols; j++) {
        const last = lastInCol(j);
        if (last !== null) {
            const goX = cx(j) - boxW / 2 - 12;
            svg += `<path d="M ${cx(j)} ${bottom(last)} L ${cx(j)} ${bottom(last) + 12} L ${goX} ${bottom(last) + 12} L ${goX} ${cy(-1)} L ${left(j)} ${cy(-1)}" class="arL" marker-end="url(#arY)"/>`;
        }
    }

    // Auto-loops: cabeças de coluna vazias
    // Estilo Ziviani: pequeno retângulo aberto ACIMA do nó, geométrico com cantos retos
    for (let j = 0; j < state.cols; j++) {
        if (firstInCol(j) === null) {
            const cxj = cx(j);
            const yTopBox = top(-1);
            const loopHalfW = 28;
            const loopH = 14;
            const cornerR = 4;

            // Path: sai da borda superior à direita, sobe (com canto arredondado), vai pra esquerda, desce voltando
            svg += `<path d="
                M ${cxj + loopHalfW} ${yTopBox}
                V ${yTopBox - loopH + cornerR}
                Q ${cxj + loopHalfW} ${yTopBox - loopH}, ${cxj + loopHalfW - cornerR} ${yTopBox - loopH}
                H ${cxj - loopHalfW + cornerR}
                Q ${cxj - loopHalfW} ${yTopBox - loopH}, ${cxj - loopHalfW} ${yTopBox - loopH + cornerR}
                V ${yTopBox - 1}
            " class="arS" marker-end="url(#arG)" fill="none"/>`;
            // Pontinho que indica o "ponteiro" (estilo Ziviani)
            svg += `<circle cx="${cxj + loopHalfW}" cy="${yTopBox}" r="2" fill="#94a3b8"/>`;

            // Texto "vazia" embaixo do nó
            svg += `<text x="${cxj}" y="${bottom(-1) + 18}" class="arS-label" text-anchor="middle">(vazia)</text>`;
        }
    }

    // Auto-loops: cabeças de linha vazias
    // Estilo Ziviani: pequeno retângulo aberto À DIREITA do nó, geométrico
    for (let i = 0; i < state.rows; i++) {
        if (firstInRow(i) === null) {
            const cyi = cy(i);
            const xRightBox = right(-1);
            const loopHalfH = 18;
            const loopW = 14;
            const cornerR = 4;

            // Path: sai da borda direita superior, vai pra direita (canto arred), desce, volta entrando pela borda direita inferior
            svg += `<path d="
                M ${xRightBox} ${cyi - loopHalfH}
                H ${xRightBox + loopW - cornerR}
                Q ${xRightBox + loopW} ${cyi - loopHalfH}, ${xRightBox + loopW} ${cyi - loopHalfH + cornerR}
                V ${cyi + loopHalfH - cornerR}
                Q ${xRightBox + loopW} ${cyi + loopHalfH}, ${xRightBox + loopW - cornerR} ${cyi + loopHalfH}
                H ${xRightBox + 1}
            " class="arS" marker-end="url(#arG)" fill="none"/>`;
            // Pontinho indicador
            svg += `<circle cx="${xRightBox}" cy="${cyi - loopHalfH}" r="2" fill="#94a3b8"/>`;

            // Texto "(vazia)" à direita do loop
            svg += `<text x="${xRightBox + loopW + 10}" y="${cyi + 4}" class="arS-label" text-anchor="start">(vazia)</text>`;
        }
    }

    svg += `</svg>`;
    structureSvg.innerHTML = svg;

    function lastInRow(i) {
        for (let k = state.cols - 1; k >= 0; k--) {
            if (state.values[i][k] !== 0) return k;
        }
        return null;
    }
    function lastInCol(j) {
        for (let k = state.rows - 1; k >= 0; k--) {
            if (state.values[k][j] !== 0) return k;
        }
        return null;
    }
}

function refresh(action) {
    updateStats(action);
    updateStructureHint();
    updateSparseView();
    renderStructure();
}

/* ============================================================
 * Construção do input para o programa C
 * ============================================================ */

function buildInput(extra) {
    if (state.rows <= 0) return null;
    const cmds = ["1", String(state.rows), String(state.cols)];
    for (const op of state.operations) {
        if (op.kind === "insert") {
            cmds.push("2", String(op.x), String(op.y), String(op.v));
        } else if (op.kind === "remove") {
            cmds.push("3", String(op.x), String(op.y));
        }
    }
    if (extra) cmds.push(...extra);
    cmds.push("0");
    return cmds.join("\n") + "\n";
}

async function runC(extra, loading) {
    const inp = buildInput(extra);
    if (inp === null) {
        setOutput("Crie uma matriz primeiro.");
        return;
    }
    setOutput(loading || "Executando programa C...");
    try {
        const response = await fetch(API_URL, {
            method: "POST",
            cache: "no-store",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ input: inp })
        });
        const data = await response.json();
        setOutput(data.output);
    } catch (err) {
        setOutput(`Erro ao executar o programa C: ${err.message}\n\nLembre-se: este painel exige rodar 'python3 server.py' na pasta interface-web.`);
    }
}

/* ============================================================
 * Event handlers
 * ============================================================ */

document.getElementById("createMatrix").addEventListener("click", async () => {
    const rows = numberFrom("rows");
    const cols = numberFrom("cols");
    if (!isInteger(rows) || !isInteger(cols) || rows <= 0 || cols <= 0) {
        setOutput("Use dimensoes maiores que zero.");
        return;
    }
    state.rows = rows;
    state.cols = cols;
    state.values = Array.from({ length: rows }, () => Array(cols).fill(0));
    state.operations = [];
    refresh(`Matriz ${rows}x${cols} criada`);
    await runC([], "Criando matriz...");
});

document.getElementById("insertValue").addEventListener("click", async () => {
    if (!hasMatrix()) return;
    const x = numberFrom("x");
    const y = numberFrom("y");
    const v = numberFrom("value");
    if (!isInteger(x) || !isInteger(y) || !isInteger(v)) {
        setOutput("Preencha linha, coluna e valor com numeros inteiros.");
        return;
    }
    if (!validPosition(x, y)) {
        await runC(["2", String(x), String(y), String(v)], "Testando insercao fora dos limites...");
        return;
    }
    state.values[x][y] = v;
    state.operations.push({ kind: "insert", x, y, v });
    state.lastChange = { x, y, kind: v === 0 ? "remove" : "insert" };
    refresh(v === 0 ? `(${x},${y}) zerada` : `Inserido ${v} em (${x},${y})`);
    setTimeout(() => { state.lastChange = null; }, 500);
    await runC([], "Inserindo valor...");
});

document.getElementById("removeValue").addEventListener("click", async () => {
    if (!hasMatrix()) return;
    const x = numberFrom("x");
    const y = numberFrom("y");
    if (!isInteger(x) || !isInteger(y)) {
        setOutput("Preencha linha e coluna com numeros inteiros.");
        return;
    }
    if (!validPosition(x, y)) {
        await runC(["3", String(x), String(y)], "Testando remocao fora dos limites...");
        return;
    }
    state.values[x][y] = 0;
    state.operations.push({ kind: "remove", x, y });
    state.lastChange = { x, y, kind: "remove" };
    refresh(`Removido (${x},${y})`);
    setTimeout(() => { state.lastChange = null; }, 500);
    await runC([], "Removendo valor...");
});

document.getElementById("consultCell").addEventListener("click", async () => {
    if (!hasMatrix()) return;
    const x = numberFrom("x");
    const y = numberFrom("y");
    if (!isInteger(x) || !isInteger(y)) {
        setOutput("Preencha linha e coluna com numeros inteiros.");
        return;
    }
    updateStats(`Consulta (${x},${y})`);
    await runC(["4", String(x), String(y)], "Consultando posicao...");
});

document.getElementById("searchValue").addEventListener("click", async () => {
    if (!hasMatrix()) return;
    const v = numberFrom("value");
    if (!isInteger(v)) {
        setOutput("Preencha o valor com um numero inteiro.");
        return;
    }
    updateStats(`Busca por ${v}`);
    await runC(["5", String(v)], "Buscando valor...");
});

document.getElementById("showNeighbors").addEventListener("click", async () => {
    if (!hasMatrix()) return;
    const x = numberFrom("x");
    const y = numberFrom("y");
    if (!isInteger(x) || !isInteger(y)) {
        setOutput("Preencha linha e coluna com numeros inteiros.");
        return;
    }
    updateStats(`Vizinhos de (${x},${y})`);
    await runC(["6", String(x), String(y)], "Buscando vizinhos...");
});

document.getElementById("clearMatrix").addEventListener("click", () => {
    state.rows = 0;
    state.cols = 0;
    state.values = [];
    state.operations = [];
    state.lastChange = null;
    sparseView.textContent = "Nenhum valor inserido.";
    structureSvg.innerHTML = `<p class="placeholder">A estrutura aparece aqui apos criar uma matriz.</p>`;
    updateStructureHint();
    updateStats("Limpa");
    setOutput("Crie uma matriz para comecar.");
    clearNarration();
});

/* ============================================================
 * Demo animada didática: mostra o algoritmo de inserção passo a passo
 * ============================================================ */

const narration = document.getElementById("narration");

function narrate(text) {
    narration.classList.remove("hidden");
    narration.textContent = text;
}

function clearNarration() {
    narration.classList.add("hidden");
    narration.textContent = "";
}

function highlight(elementId, kind) {
    const el = document.getElementById(elementId);
    if (el) el.classList.add(kind || "highlight-walk");
}

function unhighlight(elementId) {
    const el = document.getElementById(elementId);
    if (el) {
        el.classList.remove("highlight-walk");
        el.classList.remove("highlight-target");
    }
}

function clearAllHighlights() {
    document.querySelectorAll(".highlight-walk, .highlight-target, .highlight-anchor, .highlight-link").forEach((el) => {
        el.classList.remove("highlight-walk");
        el.classList.remove("highlight-target");
        el.classList.remove("highlight-anchor");
        el.classList.remove("highlight-link");
    });
}

async function animatedInsert(x, y, v, speed) {
    const pause = speed;
    const shortPause = Math.max(300, speed / 2);

    clearAllHighlights();

    // Passo 1: Começa no principal
    narrate(`Inserir (${x}, ${y}) = ${v}. Começando do nó principal.`);
    highlight("el-principal", "highlight-target");
    await sleep(pause);
    unhighlight("el-principal");

    // Passo 2: acharCabecaLinha — começa em principal->abaixo (= cab_lin_0) e caminha "linha" passos
    narrate(`acharCabecaLinha(${x}): saindo do principal pelo ponteiro 'abaixo', chegamos em cab_lin_0. Depois caminhamos ${x} passo${x !== 1 ? "s" : ""} via 'abaixo'.`);
    await sleep(shortPause);

    for (let i = 0; i <= x; i++) {
        highlight(`el-cablin-${i}`, "highlight-walk");
        if (i === 0) {
            narrate(`Chegamos em cab_lin_0${i === x ? " — esta é a cabeça que procuramos." : ", precisamos continuar até cab_lin_" + x + "."}`);
        } else {
            narrate(`Caminhando: cab_lin_${i - 1}.abaixo = cab_lin_${i}${i === x ? " — encontramos!" : "."}`);
        }
        await sleep(shortPause);
        if (i < x) unhighlight(`el-cablin-${i}`);
    }

    document.getElementById(`el-cablin-${x}`).classList.remove("highlight-walk");
    document.getElementById(`el-cablin-${x}`).classList.add("highlight-target");
    await sleep(pause);

    // Passo 3: acharCabecaColuna
    narrate(`acharCabecaColuna(${y}): saindo do principal pelo ponteiro 'direita', chegamos em cab_col_0. Depois caminhamos ${y} passo${y !== 1 ? "s" : ""} via 'direita'.`);
    await sleep(shortPause);

    for (let j = 0; j <= y; j++) {
        highlight(`el-cabcol-${j}`, "highlight-walk");
        if (j === 0) {
            narrate(`Chegamos em cab_col_0${j === y ? " — esta é a cabeça que procuramos." : ", precisamos continuar até cab_col_" + y + "."}`);
        } else {
            narrate(`Caminhando: cab_col_${j - 1}.direita = cab_col_${j}${j === y ? " — encontramos!" : "."}`);
        }
        await sleep(shortPause);
        if (j < y) unhighlight(`el-cabcol-${j}`);
    }

    document.getElementById(`el-cabcol-${y}`).classList.remove("highlight-walk");
    document.getElementById(`el-cabcol-${y}`).classList.add("highlight-target");
    await sleep(pause);

    // Verifica se é UPDATE (posição já tem valor)
    if (state.values[x][y] !== 0) {
        narrate(`A posição (${x}, ${y}) já tem nó armazenado. Apenas atualiza o valor para ${v} — sem criar nó novo.`);
        await sleep(shortPause);
        highlight(`el-node-${x}-${y}`, "highlight-target");
        await sleep(pause);
        state.values[x][y] = v;
        state.operations.push({ kind: "insert", x, y, v });
        state.lastChange = { x, y, kind: "insert" };
        refresh(`Atualizado (${x},${y}) = ${v}`);
        highlight(`el-node-${x}-${y}`, "highlight-target");
        await sleep(pause);
        clearAllHighlights();
        state.lastChange = null;
        return;
    }

    // Passo 4: Procurar antLinha (ponto de ancoragem na linha)
    narrate(`antLinha = cab_lin_${x}. Caminhando: enquanto antLinha.direita não for a cabeça E antLinha.direita.coluna < ${y}, avança.`);
    await sleep(shortPause);

    let antLinhaId = `el-cablin-${x}`;
    let antLinhaCol = -1;
    const existingInRow = [];
    for (let k = 0; k < state.cols; k++) {
        if (state.values[x][k] !== 0) existingInRow.push(k);
    }
    for (const col of existingInRow) {
        if (col >= y) break;
        highlight(`el-node-${x}-${col}`, "highlight-walk");
        narrate(`Visitando (${x}, ${col}): coluna ${col} < ${y}, avança. antLinha = (${x}, ${col}).`);
        await sleep(shortPause);
        unhighlight(`el-node-${x}-${col}`);
        antLinhaId = `el-node-${x}-${col}`;
        antLinhaCol = col;
    }

    // Destaca antLinha final
    document.getElementById(antLinhaId).classList.remove("highlight-walk");
    document.getElementById(antLinhaId).classList.add("highlight-anchor");
    if (antLinhaCol === -1) {
        narrate(`antLinha = cab_lin_${x} (a lista da linha estava vazia ou o novo será o primeiro). Ponto de ancoragem para inserção.`);
    } else {
        narrate(`antLinha = (${x}, ${antLinhaCol}). É o último nó com coluna < ${y}. Aqui faremos a religação.`);
    }
    await sleep(pause);

    // Passo 5: Procurar antColuna
    narrate(`antColuna = cab_col_${y}. Caminhando: enquanto antColuna.abaixo não for a cabeça E antColuna.abaixo.linha < ${x}, avança.`);
    await sleep(shortPause);

    let antColunaId = `el-cabcol-${y}`;
    let antColunaRow = -1;
    const existingInCol = [];
    for (let k = 0; k < state.rows; k++) {
        if (state.values[k][y] !== 0) existingInCol.push(k);
    }
    for (const row of existingInCol) {
        if (row >= x) break;
        highlight(`el-node-${row}-${y}`, "highlight-walk");
        narrate(`Visitando (${row}, ${y}): linha ${row} < ${x}, avança. antColuna = (${row}, ${y}).`);
        await sleep(shortPause);
        unhighlight(`el-node-${row}-${y}`);
        antColunaId = `el-node-${row}-${y}`;
        antColunaRow = row;
    }

    document.getElementById(antColunaId).classList.remove("highlight-walk");
    document.getElementById(antColunaId).classList.add("highlight-anchor");
    if (antColunaRow === -1) {
        narrate(`antColuna = cab_col_${y}. Ponto de ancoragem para inserção na coluna.`);
    } else {
        narrate(`antColuna = (${antColunaRow}, ${y}). É o último nó com linha < ${x}.`);
    }
    await sleep(pause);

    // Passo 6: Cria o nó
    narrate(`criarNode(${x}, ${y}, ${v}): aloca o novo Node com malloc. Nó nasce com auto-loop em si mesmo.`);
    await sleep(shortPause);

    state.values[x][y] = v;
    state.operations.push({ kind: "insert", x, y, v });
    state.lastChange = { x, y, kind: "insert" };
    refresh(`Inserido (${x},${y}) = ${v}`);

    // Re-destaca antLinha, antColuna e o novo nó
    if (antLinhaCol === -1) highlight(`el-cablin-${x}`, "highlight-anchor");
    else highlight(`el-node-${x}-${antLinhaCol}`, "highlight-anchor");
    if (antColunaRow === -1) highlight(`el-cabcol-${y}`, "highlight-anchor");
    else highlight(`el-node-${antColunaRow}-${y}`, "highlight-anchor");
    highlight(`el-node-${x}-${y}`, "highlight-link");
    await sleep(pause);

    // Passo 7: Religação na linha
    narrate(`Religação na linha: nova.direita ← antLinha.direita (a antiga 'direita' do antLinha agora é a 'direita' do novo nó). Depois: antLinha.direita ← nova.`);
    await sleep(pause);

    // Passo 8: Religação na coluna
    narrate(`Religação na coluna: nova.abaixo ← antColuna.abaixo. Depois: antColuna.abaixo ← nova.`);
    await sleep(pause);

    // Mostra o resultado final destacando o novo nó como "alvo"
    clearAllHighlights();
    highlight(`el-node-${x}-${y}`, "highlight-target");
    narrate(`✓ Nó (${x}, ${y}, ${v}) agora faz parte das duas listas circulares.`);
    await sleep(pause);

    clearAllHighlights();
    state.lastChange = null;
}

document.getElementById("runZiviani").addEventListener("click", async () => {
    const speed = Number.parseInt(document.getElementById("demoSpeed").value, 10) || 900;

    state.rows = 4;
    state.cols = 4;
    state.values = Array.from({ length: 4 }, () => Array(4).fill(0));
    state.operations = [];
    state.lastChange = null;

    refresh("Iniciando demo do Ziviani...");
    setOutput("Iniciando demo do Ziviani — observe a estrutura sendo construída passo a passo...");
    narrate("Matriz 4x4 criada vazia. Vamos inserir 6 valores um a um, mostrando o algoritmo.");

    await sleep(speed);

    const valores = [
        [0, 0, 50],
        [1, 0, 10],
        [1, 2, 20],
        [3, 0, -30],
        [3, 2, -60],
        [3, 3, 5]
    ];

    for (let i = 0; i < valores.length; i++) {
        const [x, y, v] = valores[i];
        narrate(`──── Inserção ${i + 1} de ${valores.length} ────`);
        await sleep(speed / 2);
        await animatedInsert(x, y, v, speed);
        refresh(`Inseridos ${i + 1}/${valores.length}`);
        await sleep(speed / 2);
    }

    narrate("Demo completa. Estrutura final igual ao exemplo do livro do Ziviani.");
    setTimeout(clearNarration, 4000);
    await runC([], "Enviando todos os comandos ao programa C...");
});

updateStats();
renderStructure();
