(function () {
  var bar = document.getElementById('reading-progress');
  if (!bar) return;

  function update() {
    var scheme = document.documentElement.getAttribute('data-md-color-scheme');
    if (scheme !== 'slate') {
      bar.style.width = '0';
      bar.style.display = 'none';
      return;
    }
    bar.style.display = 'block';
    var top = window.scrollY || document.documentElement.scrollTop;
    var h = document.documentElement.scrollHeight - window.innerHeight;
    var pct = h > 0 ? (top / h) * 100 : 0;
    bar.style.width = pct + '%';
  }

  window.addEventListener('scroll', update, { passive: true });
  window.addEventListener('resize', update, { passive: true });

  var obs = new MutationObserver(function () { update(); });
  obs.observe(document.documentElement, { attributes: true, attributeFilter: ['data-md-color-scheme'] });

  update();
})();
