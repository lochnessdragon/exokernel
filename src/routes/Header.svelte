<script>
	import { page } from '$app/stores';
	import logo from '$lib/images/svelte-logo.svg';
	import github from '$lib/images/github.svg';

	let y = 0;
</script>

<svelte:window bind:scrollY={y} />

<header class="sticky top-0 p-4 transition-colors" class:bg-indigo-900={y >= 10}>
	<nav>
		<ul class="flex text-slate-500 font-bold">
			<li class="grow flex-auto basis-1/4 text-center" aria-current={$page.url.pathname === '/' ? 'page' : undefined}>
				<a href="/">Home</a>
			</li>
			<li class="grow flex-auto basis-1/4 text-center"><a href="#features">Features</a></li>
			<li class="grow flex-auto basis-1/4 text-center"><a href="#docs">Guides</a></li>
			<li class="grow flex-auto basis-1/4 text-center"><a href="#contributing">Contributing</a></li>
		</ul>
	</nav>
</header>