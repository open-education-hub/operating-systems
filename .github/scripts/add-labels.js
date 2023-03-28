async function getPRFileData(github, context, pr) {
    return await github.request('GET /repos/{owner}/{repo}/pulls/{pull_number}/files', {
        owner: context.repo.owner,
        repo: context.repo.repo,
        pull_number: pr
    })
}

function addLabelToList(labels, label) {
    if (!labels.includes(label)) {
        labels.push(label)
    }
}

async function createLabelsForPR(github, context, pr) {
    var labels = []

    await getPRFileData(github, context, pr).then((data) => {
        data.data.forEach((file) => {
            if (file.status === 'added') {
                addLabelToList(labels, 'kind/new')
            }
            else if (file.status === 'modified' && file.deletions === 0 && file.additions > 0) {
                addLabelToList(labels, 'kind/improve')
            }
        })
    })

    return labels
}

async function addLabelsToPR(github, context, pr, labels) {
    if (labels.length === 0) {
        return
    }

    await github.request('POST /repos/{owner}/{repo}/issues/{issue_number}/labels', {
        owner: context.repo.owner,
        repo: context.repo.repo,
        issue_number: pr,
        labels: labels
    })
}

export default async function assignLabelsToPRs({github, context})
{
    await github.request('GET /repos/{owner}/{repo}/pulls', {
        owner: context.repo.owner,
        repo: context.repo.repo
    }).then((prs) => { prs.data.forEach(async (pr) => {
        if (pr.state == 'open') {
            const prNum = pr.number
            const labels = await createLabelsForPR(github, context, prNum)
            if (labels.length > 0) {
                await addLabelsToPR(github, context, prNum, labels)
            }
        }
    })})
}
