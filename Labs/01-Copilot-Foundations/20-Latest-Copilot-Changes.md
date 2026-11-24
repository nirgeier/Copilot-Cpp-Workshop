# 20. Latest Copilot Changes

!!! abstract "About this Lab"
    This lab records the GitHub Copilot releases from 17 and 18 November 2026 and maps each change to the workshop. Check the linked changelog articles before teaching a feature, because public preview features can change.

## 1. Source and Scope

All items below come from the GitHub Changelog with the `copilot` label. The ten newest entries at the time of writing cover 17 and 18 November 2026. Treat a public preview item as subject to change and an item with a date as a point in time, not a promise about your tenant.

| Date | Release | Workshop status before this lab |
|------|---------|---------------------------------|
| 18 Nov | Eight more connectors | Partial, generic MCP coverage only |
| 18 Nov | Gemini 4 Neon | Missing |
| 18 Nov | Team customizations for plugins | Missing |
| 17 Nov | GPT-6.2 Astra and Sol | Missing |
| 17 Nov | Copilot Fusion updates | Partial, one mention in Lab 07 |
| 17 Nov | Copilot app at Microsoft Ignite | Missing |
| 17 Nov | Copilot code review updates | Partial, Adaptive effort only |
| 17 Nov | MAI Code 2 and MAI Code 2 Flash | Missing |
| 17 Nov | JetBrains at Microsoft Ignite | Missing |
| 17 Nov | Activity monitoring through Agent 365 | Missing |

## 2. Eight More Connectors

GitHub-verified MCP servers, called connectors, now include Box, Buildkite, Calendly, ClickUp, Mixpanel, Supabase, Webflow, and Wix. They join more than 25 existing services such as Slack, Figma, and Sentry. They are in public preview for all plans.

=== "Copilot CLI"

    ```text
    /mcp
    -> Connectors tab
    -> Connect on the service you need

    Example prompt: "Why did the latest Buildkite build fail, and fix the code."
    ```

=== "Copilot app"

    ```text
    Customize -> select Connect on the service
    ```

=== "VS Code"

    ```text
    Agents window -> Customizations -> connect the service
    ```

=== "github.com"

    ```text
    Copilot customization page -> select the service -> Connect
    ```

!!! warning "Admin requirements"
    For Copilot Business or Enterprise, an administrator must enable the **Editor preview features** policy. If the enterprise MCP allowlist names connectors individually instead of using a wildcard, the new connectors must be added to it. Some services also need admin side enablement, such as allowing Box MCP access.

Ground this in Lab 12: connect one approved service, list its tools, and grant only the tools the task needs.

## 3. Team Customizations for Plugins

Team customizations are generally available for organization teams. Team maintainers and organization owners can select approved Agent Plugins as team defaults. This sits between individual customization and organization wide policy.

- Open the organization team on github.com and select **Customize Copilot**.
- Browse plugins from built in marketplaces, enterprise marketplaces, and marketplaces added by the team.
- Add a marketplace from a GitHub repository that contains a plugin marketplace, then enable individual plugins.
- Selected plugins are enabled by default for direct members in VS Code, the Copilot app, and Copilot CLI.
- Child teams do not inherit them. Team defaults are optional and members can turn a plugin off where policy permits.
- Enterprise and organization policies take precedence over team choices.
- Available for Copilot Business and Copilot Enterprise.

```text
Team: cpp-platform
  default plugins: [approved-review-plugin, approved-test-plugin]
  marketplaces: [built-in, enterprise-marketplace, team-marketplace]
  inherited by child teams: no
  member opt-out: yes, where policy permits
  policy overrides: enterprise and organization policies win
```

## 4. New Models

Three announcement posts added models to the picker. The workshop uses `<approved-model-id>` placeholders, so add the names to Lab 07 when your tenant has them.

=== "Gemini 4 Neon"

    ```text
    Status: generally available
    Plans: Pro+, Max, Business, Enterprise
    Strength: agentic coding, multistep tool use, knowledge work
    Vendor claim: close to Gemini 4 Carbon quality at lower token cost per task,
      faster first response, fewer unrequested changes, fewer unsupported claims.
    Billing: provider list pricing under usage-based billing
    Access: model policy in Copilot settings
    ```

=== "GPT-6.2 Astra and Sol"

    ```text
    Status: generally available
    Plans: Pro+, Max, Business, Enterprise
    Astra: agentic coding and terminal work; fewer tokens than GPT-6 Astra.
    Sol: complex agentic coding and in-depth code review; nearly twice as many
      real issues found as GPT-6.1 Sol in early testing.
    Billing: provider list pricing under usage-based billing
    Access: model policy in Copilot settings
    ```

=== "MAI Code 2 and Flash"

    ```text
    Status: generally available
    Code 2: deep debugging, multi-file implementation, refactoring,
      repository-wide reasoning. Pro+, Max, Business, Enterprise.
    Flash: code explanations, targeted edits, routine fixes, rapid iteration.
      Free, Student, Pro, Pro+, Max, Business, Enterprise.
    Billing: GitHub AI credits under usage-based billing
    Access: model policy in Copilot settings
    ```

!!! note "Model policy"
    New models are enabled automatically under default model enablement unless an administrator turned off the global default or explicitly disabled the model. Granular per model control is in preview. Check the supported models reference for current client availability.

## 5. Copilot Fusion Updates

Fusion is the system that chooses and coordinates models for a task. You pick Fusion in the model picker and set an effort level.

- Fusion is listed on public Terminal-Bench 4.1 leaderboards from Stanford, Harbor, and the Laude Institute. Fusion Max scored 71.2 percent resolution, 5.4 points ahead of Opus 5.5 and Fable 5.2, at 88 percent less cost than Fable 5.2 and 57 percent less than Opus 5.5. Quote the article and its date, not a fresh benchmark.
- Fusion is selectable on the latest github.com, Visual Studio, and GitHub Mobile beta apps for iOS and Android. Production mobile support was described as coming shortly.
- Effort tiers in this release: Standard, High, and Max.
- Component models: Claude Sonnet 5.5 in Fusion Max, GPT-6.1 Terra in Fusion High, and MAI-Code-2 in Fusion Standard.

```text
Model picker: Copilot Fusion
Effort: Max
Use for: hard terminal tasks, cross-cutting C++ debugging
Record: displayed effort, surface, credits, and the exact prompt
```

## 6. Copilot App at Microsoft Ignite

- **Azure DevOps repositories**, public preview: clone a repo, create a branch, make changes, and open a pull request from the Copilot app. Track status in the sidebar, use Fix on a review comment, and enable agent merge so an agent fixes CI failures and completes the PR once Azure DevOps checks pass. Cloud sessions are not available for Azure DevOps repositories. Enable it under Settings > Experimental, then Accounts > Add account.
- **Browser use**, public preview: the Chrome extension lets Copilot fill forms, read pages, and test or debug a web app in an isolated tab group with Chromium browsers such as Chrome and Edge. It is off by default. Install the extension, then enable both Computer Use and Browser Use under Settings > Computer Use. Browser use also exists in Copilot CLI, VS Code, and JetBrains.
- **GitHub Enterprise Server**: you can bring your GHES instance into the app.

!!! warning "Classroom fit"
    This workshop uses github.com and a local C++ checkout. Treat Azure DevOps, GHES, and browser use as awareness items unless your organization uses them.

## 7. Copilot Code Review Updates

Five changes shipped together. Adaptive effort was the only one previously mentioned in the workshop.

=== "Adaptive effort"

    ```text
    Status: public preview
    Behavior: Copilot reads pull request complexity and risk, then picks
      Lite, Balanced, or Max. Each review shows the level it picked.
    Select per PR from the Reviewers bar, or set a default in personal,
    repository, organization, or enterprise settings.
    Balanced stays the default. Adaptive never exceeds the configured maximum.
    ```

=== "Cross-repository context"

    ```text
    Status: public preview
    Behavior: reviews can use related public repositories' default branches
    to find dependent code and documentation.
    Admin control: the "Search public repositories" setting.
    ```

=== "Secret detection"

    ```text
    Status: public preview
    Behavior: flags exposed credentials in review comments before merge.
    Deterministic: 500+ secret types from 150+ partners through the
      secret scanning partnership program.
    AI/ML: detects secrets without a recognizable format.
    Enable: repository or organization settings > Copilot > Code review.
    ```

=== "Repository insights"

    ```text
    Open a repository > Insights tab > Repository insights.
    Shows how Copilot review feedback is addressed and used per repository.
    Lab 09 already introduces repository insights as an admin view.
    ```

=== "Azure Repos"

    ```text
    Status: generally available
    Setup: organization, project, or repository level; add a branch policy to
      request Copilot review automatically, or request it from Reviewers.
    Effort: Lite or Balanced default, or choose per review.
    Custom instructions and agent skills tailor feedback.
    Audit log records enable, disable, and settings changes.
    Billing: GitHub AI credits to the Azure subscription linked to the
      Azure DevOps organization.
    ```

## 8. JetBrains at Microsoft Ignite

- **Cloud sandbox**, public preview: sessions run in an isolated GitHub hosted environment instead of locally. Copilot can edit, run commands, and run tests there, and parallel sessions are possible.
- **Remote access**, public preview: expose a JetBrains chat to other Copilot clients such as VS Code and the Copilot app, or reopen a remote session from history.
- **Browser use**, public preview: with the GitHub Copilot Chrome extension, enable it under GitHub Copilot > Chat > Enable Browser Use.
- **On-device voice dictation**, public preview: supported native plugin packages with Editor Preview enabled; download a model and opt in. Transcripts remain editable drafts until Send.
- **Split mode remote development**: chat and editor UI on the local client, Copilot operations on the remote backend. Install the plugin in both places.
- User experience: conversation timing, context usage shortcuts, historical diffs, simpler follow-up controls, and chat reliability improvements.

## 9. Activity Monitoring Through Microsoft Agent 365

- Enterprises can stream GitHub Copilot audit activity into Microsoft Agent 365.
- Coverage includes cloud agents on github.com, Copilot CLI, VS Code, Visual Studio, and partner IDEs such as JetBrains and Eclipse.
- Administrators can review user sessions with prompts, responses, and tool calls, and view usage trends in Agent 365.
- Additional risk context is available in Microsoft Purview and Defender.
- Requirement: GitHub Enterprise Cloud with Enterprise Managed Users. Setup uses enterprise audit log streaming.

```text
Audit stream: GitHub enterprise -> Microsoft Agent 365
Visible: prompts, responses, tool calls, usage trends
Risk context: Microsoft Purview, Microsoft Defender
Scope: Enterprise Cloud with Enterprise Managed Users
Workshop link: Lab 09 for GitHub native usage metrics and audit log review
```

## 10. Where to Apply This in the Course

| Release item | Update these labs |
|--------------|-------------------|
| Connectors | Lab 12 and task 09 |
| Team customizations | Lab 01 alignment and Lab 06 agent roles |
| New models | Lab 07 and task 04 |
| Fusion | Lab 07 |
| Copilot app | Lab 01 alignment |
| Code review updates | Lab 10 and task 07 |
| JetBrains features | Lab 13 agent mode |
| Agent 365 | Lab 09 and task 06 |

## Sources

- [Eight more connectors](https://github.blog/changelog/2026-11-18-connect-supabase-box-calendly-and-more-to-copilot)
- [Gemini 4 Neon](https://github.blog/changelog/2026-11-18-gemini-4-neon-in-github-copilot)
- [Team customizations](https://github.blog/changelog/2026-11-18-customize-github-copilot-for-your-team)
- [GPT-6.2 Astra and Sol](https://github.blog/changelog/2026-11-17-openais-gpt-6-2-astra-and-gpt-6-2-sol-now-available)
- [Fusion updates](https://github.blog/changelog/2026-11-17-github-copilot-fusion-updates-more-availability-benchmarks-and-models)
- [Copilot app at Ignite](https://github.blog/changelog/2026-11-17-github-copilot-app-microsoft-ignite-releases)
- [Copilot code review updates](https://github.blog/changelog/2026-11-17-copilot-code-review-adaptive-effort-secret-detection-and-more)
- [MAI Code 2 and Flash](https://github.blog/changelog/2026-11-17-mai-code-2-and-mai-code-2-flash-in-github-copilot)
- [JetBrains at Ignite](https://github.blog/changelog/2026-11-17-github-copilot-in-jetbrains-ignite-releases)
- [Agent 365 monitoring](https://github.blog/changelog/2026-11-17-monitor-github-copilot-activity-through-microsoft-agent-365)

## 11. Definition of Done

- [ ] Each release item above is traceable to a linked changelog article.
- [ ] Public preview items are labeled as such in your notes.
- [ ] Your tenant was checked for the models and features you plan to demo.
- [ ] The relevant existing labs were updated or you recorded a gap with an owner.
- [ ] No benchmark number is quoted without its article and date.

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

## 12. Summary

&emsp;✅&emsp;Name the November 2026 Copilot releases and their status<br>
&emsp;✅&emsp;Map each release item to the lab that should teach it<br>
&emsp;✅&emsp;Distinguish general availability from public preview in your notes

**Back:** [Foundations overview](README.md) and [Documentation map](19-Official-Documentation-Map.md)
